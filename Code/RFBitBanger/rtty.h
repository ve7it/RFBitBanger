
/*  rtty.h */

/*
 * Copyright (c) 2021 Daniel Marks

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

#ifndef __RTTY_H
#define __RTTY_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _rtty_state
{
  uint8_t   protocol;
} rtty_state;

void rtty_new_sample(void);
void rtty_decode_process(void);
uint8_t rtty_txmit(dsp_txmit_message_state *dtms, dsp_dispatch_callback ddc);

#ifdef __cplusplus
}
#endif

#endif  /* __RTTY_H */
