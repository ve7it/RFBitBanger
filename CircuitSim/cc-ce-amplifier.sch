<Qucs Schematic 0.0.22>
<Properties>
  <View=0,0,1309,875,1,0,113>
  <Grid=10,10,1>
  <DataSet=cc-ce-amplifier.dat>
  <DataDisplay=cc-ce-amplifier.dpl>
  <OpenDisplay=1>
  <Script=cc-ce-amplifier.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <GND * 1 200 240 0 0 0 0>
  <Vdc V2 1 200 180 18 -26 0 1 "12 V" 1>
  <_BJT Q2N3904_1 1 430 390 8 -26 0 0 "npn" 0 "1.4e-14" 0 "1" 0 "1" 0 "0.025" 0 "0" 0 "100" 0 "0" 0 "3e-13" 0 "1.5" 0 "0" 0 "2" 0 "300" 0 "7.5" 0 "0" 0 "0" 0 "2.4" 0 "0" 0 "0" 0 "4.5e-12" 0 "0.75" 0 "0.33" 0 "3.5e-12" 0 "0.75" 0 "0.33" 0 "1" 0 "0" 0 "0.75" 0 "0" 0 "0.5" 0 "4e-10" 0 "0" 0 "0" 0 "0" 0 "2.1e-08" 0 "26.85" 0 "9e-16" 0 "1" 0 "1" 0 "0" 0 "1" 0 "1" 0 "0" 0 "1.5" 0 "3" 0 "1.11" 0 "26.85" 0 "1" 0>
  <R R4 1 430 490 15 -26 0 1 "1k Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 430 560 0 0 0 0>
  <_BJT Q2N3904_2 1 600 430 8 -26 0 0 "npn" 0 "1.4e-14" 0 "1" 0 "1" 0 "0.025" 0 "0" 0 "100" 0 "0" 0 "3e-13" 0 "1.5" 0 "0" 0 "2" 0 "300" 0 "7.5" 0 "0" 0 "0" 0 "2.4" 0 "0" 0 "0" 0 "4.5e-12" 0 "0.75" 0 "0.33" 0 "3.5e-12" 0 "0.75" 0 "0.33" 0 "1" 0 "0" 0 "0.75" 0 "0" 0 "0.5" 0 "4e-10" 0 "0" 0 "0" 0 "0" 0 "2.1e-08" 0 "26.85" 0 "9e-16" 0 "1" 0 "1" 0 "0" 0 "1" 0 "1" 0 "0" 0 "1.5" 0 "3" 0 "1.11" 0 "26.85" 0 "1" 0>
  <GND * 1 600 560 0 0 0 0>
  <GND * 1 740 390 0 0 0 0>
  <C C3 1 490 430 -5 16 0 2 "100 nF" 1 "" 0 "neutral" 0>
  <GND * 1 100 560 0 0 0 0>
  <Vac V1 1 100 460 18 -26 0 1 "1 mV" 1 "1 GHz" 0 "0" 0 "0" 0>
  <C C2 1 640 290 -26 -55 0 2 "100 nF" 1 "" 0 "neutral" 0>
  <IProbe Pr2 1 710 290 -26 16 0 0>
  <R R1 1 130 390 -26 -53 0 2 "50 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R6 1 740 340 15 -26 0 1 "50 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <C C1 1 290 390 -26 -55 0 2 "100 nF" 1 "" 0 "neutral" 0>
  <IProbe Pr1 1 220 390 -26 16 0 0>
  <R R3 1 340 280 -100 -26 0 3 "10k Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <C C4 1 340 440 -89 -26 0 3 "100 nF" 1 "" 0 "neutral" 0>
  <GND * 1 340 570 0 0 0 0>
  <R R8 1 550 330 -100 -26 0 3 "10k Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R7 1 600 210 -101 -26 0 3 "470 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <.DC DC1 1 20 130 0 39 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <.AC AC1 1 20 210 0 39 0 0 "log" 1 "100 kHz" 1 "100 MHz" 1 "101" 1 "no" 0>
  <R R10 1 340 510 -92 -26 0 3 "50 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <.NOISE NOISE1 1 150 590 0 63 0 0 "log" 1 "100 kHz" 1 "100 MHz" 1 "300" 1 "v(OutputV)" 1 "V1" 1>
</Components>
<Wires>
  <200 210 200 240 "" 0 0 0 "">
  <200 140 200 150 "" 0 0 0 "">
  <200 140 340 140 "" 0 0 0 "">
  <340 140 430 140 "" 0 0 0 "">
  <430 420 430 430 "" 0 0 0 "">
  <430 520 430 560 "" 0 0 0 "">
  <600 240 600 290 "" 0 0 0 "">
  <600 140 600 180 "" 0 0 0 "">
  <550 430 570 430 "" 0 0 0 "">
  <600 290 600 400 "" 0 0 0 "">
  <520 430 550 430 "" 0 0 0 "">
  <430 430 430 460 "" 0 0 0 "">
  <430 430 460 430 "" 0 0 0 "">
  <550 360 550 430 "" 0 0 0 "">
  <550 290 600 290 "" 0 0 0 "">
  <550 290 550 300 "" 0 0 0 "">
  <100 490 100 560 "" 0 0 0 "">
  <600 290 610 290 "" 0 0 0 "">
  <670 290 680 290 "" 0 0 0 "">
  <100 390 100 430 "" 0 0 0 "">
  <740 290 740 310 "" 0 0 0 "">
  <740 370 740 390 "" 0 0 0 "">
  <320 390 340 390 "" 0 0 0 "">
  <340 310 340 390 "" 0 0 0 "">
  <340 140 340 250 "" 0 0 0 "">
  <250 390 260 390 "" 0 0 0 "">
  <160 390 190 390 "InputV" 120 410 18 "">
  <430 140 600 140 "" 0 0 0 "">
  <430 140 430 360 "" 0 0 0 "">
  <340 540 340 570 "" 0 0 0 "">
  <340 470 340 480 "" 0 0 0 "">
  <340 390 340 410 "" 0 0 0 "">
  <600 460 600 560 "" 0 0 0 "">
  <340 390 400 390 "" 0 0 0 "">
  <740 290 740 290 "OutputV" 770 260 0 "">
</Wires>
<Diagrams>
  <Rect 916 383 299 213 3 #c0c0c0 1 13 1 100000 1 1e+08 1 0.0003 1 0.003 1 0.01 1 0.1 315 0 225 "" "" "">
	<"ngspice/ac.v(outputv)" #0000ff 0 3 0 0 0>
	<"ngspice/ac.v(inputv)" #ff0000 0 3 0 0 1>
  </Rect>
  <Rect 926 683 299 213 3 #c0c0c0 1 13 1 100000 1 1e+08 1 3e-07 1 0.03 1 -1 0.5 1 315 0 225 "" "" "">
	<"ngspice/ac.i(pr1)" #ff0000 0 3 0 0 0>
	<"ngspice/ac.i(pr2)" #ff00ff 0 3 0 0 1>
  </Rect>
  <Rect 460 780 240 160 3 #c0c0c0 1 10 1 100000 1 1e+08 1 1e-09 1 3e-09 1 2e-08 1e-08 4e-08 315 0 225 "" "" "">
	<"ngspice/ac.inoise_spectrum" #0000ff 0 3 0 0 0>
	<"ngspice/ac.onoise_spectrum" #ff0000 0 3 0 0 1>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
