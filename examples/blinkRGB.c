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

// LED is annode common.
#define ON  0
#define OFF 1
#define END 9

#define ON_TIME		1
#define OFF_TIME	3
#define INTV_TIME	4



int data [] =
{
 // White
            4, ON, 0,  // Red
            5, ON, 0, // Green
            6, ON, ON_TIME, // Blue
  4, OFF, 0,
  5, OFF, 0,
  6, OFF, INTV_TIME,	// Extra delay

// single color
            4, ON, ON_TIME,  // Red
  4, OFF, OFF_TIME,
            5, ON, ON_TIME, // Green
  5, OFF, OFF_TIME,
            6, ON, ON_TIME, // Blue
  6, OFF, INTV_TIME,	// Extra delay

// dual color on
            4, ON, 0,  // Red
            5, ON, ON_TIME, // Green
  4, OFF, 0,
  5, OFF, OFF_TIME,
            5, ON, 0, // Green
            6, ON, ON_TIME, // Blue
  5, OFF, 0,
  6, OFF, OFF_TIME,
            6, ON, 0, // Blue
            4, ON, ON_TIME,  // Red
  6, OFF, 0,
  4, OFF, OFF_TIME,
// extra Delay
  4, OFF, INTV_TIME,	// Extra delay
  4, END, 0,	// End marker

} ;


int main (int ac, char **av)
{
  int pin ;
  int dataPtr ;
  int l, s, d ;

  printf ("Raspberry Pi - RGB-LED Sequence\n") ;
  printf ("==============================\n") ;
  printf ("\n") ;
  printf ("Connect LEDs up to the first GPIO #(4,5,6) to (R,G,B)\n") ;

  wiringPiSetup () ;

  for (pin = 4 ; pin < 7 ; ++pin)
    pinMode (pin, OUTPUT) ;

  if (ac > 1) {
    l = atoi(av[1]) & 0x07;
    printf ("Set LED to %d=0b(R,G,B)\n", l) ;
    digitalWrite (4, l & 4 ? ON : OFF) ; // Red
    digitalWrite (5, l & 2 ? ON : OFF) ; // Green
    digitalWrite (6, l & 1 ? ON : OFF) ; // Blue
    return 0 ;
  }	

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
