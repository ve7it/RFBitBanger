/* RFBitBanger.ino

*/

/*
   Copyright (c) 2021 Daniel Marks

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <Arduino.h>
#include <wiring_private.h>
#include <avr/pgmspace.h>
#include "si5351simple.h"
#include "LiquidCrystalButtons.h"
#include "PS2Keyboard.h"
#include "RFBitBanger.h"
#include "ui.h"

#include "dspint.h"
#include "cwmod.h"
#include "scamp.h"

#define LCDB_RS A3
#define LCDB_E A2
#define LCDB_DB4 5
#define LCDB_DB5 6
#define LCDB_DB6 7
#define LCDB_DB7 8

#define TRANSMIT_PIN 9
#define BACKLIGHT_PIN 11
#define MUTEAUDIO_PIN 4
#define BEEPOUT_BIN 3

LiquidCrystalButtons lcd(LCDB_RS, LCDB_E, LCDB_DB4, LCDB_DB5, LCDB_DB6, LCDB_DB7);
si5351simple si5351(8,27000000u);
PS2Keyboard PSkey;

const char mainmenutitle[] PROGMEM = "Menu";
const char mainmenu1[] PROGMEM = "Optionmenu1";
const char mainmenu2[] PROGMEM = "Optionmenu2";
const char mainmenu3[] PROGMEM = "Optionmenu3";
const char mainmenu4[] PROGMEM = "Optionmenu4";
const char mainmenu5[] PROGMEM = "Optionmenu5";
const char mainmenu6[] PROGMEM = "Optionmenu6";
const char mainmenu7[] PROGMEM = "Optionmenu7";

const char *const mainmenu[] PROGMEM = {mainmenu1,mainmenu2,mainmenu3,mainmenu4,mainmenu5,mainmenu6,mainmenu7,NULL };

const char freqmenutitle[] PROGMEM = "Freq";

void setupADC() {
  ADCSRA = 0;
  PRR &= ~PRADC;
  ADCSRB = (1 << ADTS2) | (1 << ADTS1);
  ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS1) | (1 << ADPS0);
  ADMUX = (1 << REFS0);
}

void idle_task(void)
{
  lcd.pollButtons();
}

#define PROCESSOR_CLOCK_FREQ 16000000
#define TIMER1_INTERRUPT_FREQ 4000
#define TIMER1_COUNT_MAX (PROCESSOR_CLOCK_FREQ / TIMER1_INTERRUPT_FREQ)

volatile uint16_t adc_sample_0;
volatile uint16_t adc_sample_1;

volatile uint16_t melapsed;

ISR(TIMER1_OVF_vect)
{
  static uint8_t last_adc1 = 0;
  uint16_t adc_sample;
  do
  { uint8_t low = ADCL;
    uint8_t high = ADCH;
    adc_sample = (((uint16_t) high) << 8) | low;
  } while (0);
  sei();
  uint16_t m2 = micros();
  if (last_adc1)
  {
    last_adc1 = 0;
    adc_sample_1 = adc_sample;
    ADMUX = (1 << REFS0) | 0x01;
  } else
  {
    last_adc1 = 1;
    adc_sample_0 = adc_sample;
    ADMUX = (1 << REFS0);
    dsp_interrupt_sample(adc_sample);
  }
  melapsed = micros() - m2;
}

void write_transmit_pwm(uint16_t pwm)
{
  OCR1AH = pwm >> 8;
  OCR1AL = pwm & 0xFF;
}

void write_tuning_pwm(uint16_t pwm)
{
  OCR1BH = pwm >> 8;
  OCR1BL = pwm & 0xFF;
}

void setup_timers(void)
{
  cli();
  // WGM13 = 1, WGM12 = 1, WGM11 = 1, WGM10 = 0
  TCCR1A = (1<<COM1B1) | (1<<WGM11);  
  TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS10);
  ICR1H = (TIMER1_COUNT_MAX >> 8);
  ICR1L = (TIMER1_COUNT_MAX & 0xFF);
  write_transmit_pwm(1);
  write_tuning_pwm(0);
  TIMSK1 = (1<<TOIE1);

  TIMSK2 = 0;
  sei();
}

uint8_t tone_state = 0;
uint8_t tone_last_freq = 0;

void tone_off(void)
{
  if (tone_state)
  {
    pinMode(BEEPOUT_BIN,INPUT);
    tone_state = 0;
  }
}

#define TONEFREQ_BASEFREQ (16000000ul / 256)
#define TONEFREQ(x) (TONEFREQ_BASEFREQ / (x))
#define TONEFREQVOL(x,vol) (((TONEFREQ_BASEFREQ / (x)) * (vol)) >> 8)
#define TONE_ON(freq,vol) tone_on(TONEFREQ(freq),TONEFREQVOL(freq,vol))
#define TONE_OFF() tone_off()

void tone_on(uint8_t freq, uint8_t vol)
{
  if ((!tone_state) || (freq != tone_last_freq))
  {
    if (!tone_state) pinMode(BEEPOUT_BIN,OUTPUT);  
    TCCR2B = 0;
    OCR2A = freq;
    OCR2B = vol;
    TCNT2 = 0;
    TCCR2A = (1<<COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << WGM22) | (1<<CS22) | (1<<CS21);   // 256 divider
    tone_last_freq = freq;
    tone_state = 1;
  } else
    OCR2B = vol;
}

void setup() {
  dsp_initialize_open();
  setupADC();
  setup_timers();
  PSkey.begin();
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(TRANSMIT_PIN,OUTPUT);
  pinMode(BACKLIGHT_PIN,OUTPUT);
  pinMode(MUTEAUDIO_PIN,OUTPUT);
  TONE_OFF();
  si5351.start();
  lcd.begin(20,4);
  digitalWrite(TRANSMIT_PIN,LOW);
  digitalWrite(MUTEAUDIO_PIN,LOW);
  digitalWrite(BACKLIGHT_PIN,HIGH);
}

#define UPDATE_MILLIS_BARS 100

uint8_t map_16_to_bar(uint16_t b)
{
  if (b < 64)
    return (b >> 3);                  // 0 to 64 is 0 to 7
  if (b < 192)
    return (b >> 4) + 4;              // 64 to 192 is 8 to 15
  if (b < 448)
    return (b >> 5) + 10;             // 192 to 448 is 16 to 23
  if (b < 960)
    return (b >> 6) + 17;             // 448 to 960 is 24 to 32
  if (b < 2048)
    return (b >> 7) + 24;             // 960 and up is 32 to 40
  return 40;
}

void sound_cue()
{
  uint8_t cueval = map_16_to_bar(ds.mag_value_16);
  //TONE_ON(625,cueval);  
}

void tune_loop()
{
  uint16_t last_update_bars;
  scroll_number_dat snd = { 12, 1, 8, 0, 0, 99999999, 0, 0, 0, 0 };
  bargraph_dat bgd = { 4, 8, 0, 0 };
  lcd.setCursor(12,0);
  lcdPrintFlash(freqmenutitle);
  scroll_number_start(&snd);
  for (;;)
  {
    idle_task();
    scroll_key(&snd);
    if (snd.changed)
    {
       snd.changed = 0;
       si5351_synth_regs s_regs;
       si5351_multisynth_regs m_regs;
  
       si5351.calc_registers(snd.n, &s_regs, &m_regs);
       si5351.set_registers(0, &s_regs, 0, &m_regs);
       si5351.setOutputOnOff(0,1);
    }
    uint16_t cur_update = millis();
    if ((cur_update - last_update_bars) >= UPDATE_MILLIS_BARS)
    {
      last_update_bars = cur_update;
      bgd.bars[0] = map_16_to_bar(ds.mag_value_20);
      bgd.bars[1] = map_16_to_bar(ds.mag_value_16);
      bgd.bars[2] = map_16_to_bar(ds.mag_value_12);
      bgd.bars[3] = map_16_to_bar(ds.mag_value_8);
      lcdBarGraph(&bgd);
    }
    sound_cue();
  }
}

#define SUBV(x,bits) ((x < 0) ? (-((-x) >> (bits))) : ((x) >> (bits)))

void loop44()
{
  static uint8_t c[]=" ";
  c[0] = PSkey.getkey();
  if (c[0] != 0xFF)
  {
    lcd.setCursor(0,0);
    lcd.print((char *)c);
  }
  delay(500);
  Serial.println(melapsed);
}

void loop() {
  tune_loop();
  //do_menu(mainmenu,mainmenutitle,0);
}
