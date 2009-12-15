
/*
                    The HumbleHacker Keyboard Project
                    Copyright � 2008, David Whetstone
               david DOT whetstone AT humblehacker DOT com

This file is a part of The HumbleHacker Keyboard Project.  

The HumbleHacker Keyboard Project is free software: you can redistribute 
it and/or modify it under the terms of the GNU General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or (at your option) any later version.  

The HumbleHacker Keyboard Project is distributed in the hope that it will 
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General 
Public License for more details.  

You should have received a copy of the GNU General Public License along 
with The HumbleHacker Keyboard Project.  If not, see 
<http://www.gnu.org/licenses/>.  

*/

#ifndef __KB_LEDS_H__
#define __KB_LEDS_H__

#include "conf_keyboard.h"

#define _250ms 0x461ffUL  // not accurate, found through trial & error

#define ON 		     1
#define OFF        0

static inline void init_leds(void);
static inline void led_on(U8 led);
static inline void led_off(U8 led);
static inline void led_set(U8 led, U8 state);
static inline void led_toggle(U8 led);
static inline void milli_pause(U16 ms);
static inline void micro_pause(U16 microsecs);

static
inline
void
init_leds(void)
{
  KB_LED_DDR  |= KB_LEDS; // set KB bits as outputs
  KB_LED_PORT |= KB_LEDS; // set KB bits high to prevent sinking (lights off)
}

static 
inline
void
led_on(U8 led)
{
  KB_LED_PORT &= ~led;
}

static 
inline
void
led_off(U8 led)
{
  KB_LED_PORT |= led;
}
   
static 
inline
void
led_set(U8 led, U8 state)
{
  if (state)
  {
    KB_LED_PORT &= ~led;
  }
  else
  {
    KB_LED_PORT |= led;
  }
}

static 
inline
void
led_toggle(U8 led)
{
  KB_LED_PORT ^= led;
}

static 
inline
void
pause(U8 secs)
{
  U32 count = secs * 4 * _250ms;
  while (--count) asm("NOP");
}

static 
inline
void
milli_pause(U16 ms)
{
  U16 count = (_250ms / 250UL) * ms;
  while (--count) asm("NOP");
}

static 
inline
void
micro_pause(U16 microsecs)
{
  U8 count = ((_250ms / 250UL) / 1000UL) * microsecs;
  while (--count) asm("NOP");
}

static 
inline
void
blink(U8 led, U8 blinks, U16 millisecs)
{
  while (blinks--)
  {
    milli_pause(millisecs);
    led_on(led);
    milli_pause(millisecs);
    led_off(led);
  }
}

#endif // __KB_LEDS_H__