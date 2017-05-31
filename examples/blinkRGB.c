/*
 * blink12.c:
 *	Simple sequence over the first 12 GPIO pins - LEDs
 *	Aimed at the Gertboard, but it's fairly generic.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

/* modified RGB LED is connected to GPIO 4,5,6=(R,G,B) */

#include <stdio.h>
#include <wiringPi.h>

// Simple sequencer data
//	Triplets of LED, On/Off and delay

int data [] =
{
  0, 0, 0,
// white
            6, 1, 2,  // Red
            5, 1, 2, // Green
            4, 1, 2, // Blue
  6, 0, 2,
  5, 0, 2,
  4, 0, 2,

  0, 0, 2,	// Extra delay

// single color
            6, 1, 2,  // Red
  6, 0, 2,
            5, 1, 2, // Green
  5, 0, 2,
            4, 1, 2, // Blue
  4, 0, 2,
  0, 0, 2,	// Extra delay

// dual color on
            6, 1, 2,  // Red
            5, 1, 2, // Green
  6, 0, 2,
  5, 0, 2,
            5, 1, 2, // Green
            4, 1, 2, // Blue
  5, 0, 2,
  4, 0, 2,
            4, 1, 2, // Blue
            6, 1, 2,  // Red

  0, 0, 2,	// Extra delay
  0, 9, 0,	// End marker

} ;


int main (void)
{
  int pin ;
  int dataPtr ;
  int l, s, d ;

  printf ("Raspberry Pi - RGB-LED Sequence\n") ;
  printf ("==============================\n") ;
  printf ("\n") ;
  printf ("Connect LEDs up to the first GPIO #(4,5,6) to (R,G,B).n") ;

  wiringPiSetup () ;

  for (pin = 4 ; pin < 7 ; ++pin)
    pinMode (pin, OUTPUT) ;

  dataPtr = 0 ;

  for (;;)
  {
    l = data [dataPtr++] ;	// LED
    s = data [dataPtr++] ;	// State
    d = data [dataPtr++] ;	// Duration (10ths)

    if (s == 9)			// 9 -> End Marker
    {
      dataPtr = 0 ;
      continue ;
    }

    digitalWrite (l, s) ;
    delay        (d * 100) ;
  }

  return 0 ;
}
