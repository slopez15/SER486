/*
File: interrupt.c
Author: Saul Lopez
Date: 4.1.17
Copyright (c) 2017

Libraries:
WiringPi is released under the GNU Lesser Public License version 3.
https://projects.drogon.net/raspberry-pi/wiringpi/ OR http://wiringpi.com/

Description:
This program is to display the use of interrupts.
I use blink program from assignment 1 as a bases.
Interrupt use: Any time a button is pressed, the program should trigger an interrupt/event where the led will light up.
*Should not use polling method!*

Self Tips:
WiringPi diagram (just write numbers on diagram to make it easy.): 
  wiring pi diagram: http://wiringpi.com/pins/
  regular diagram: http://www.jameco.com/Jameco/workshop/circuitnotes/raspberry_pi_circuit_note_fig2a.jpg
  regular diagram (multi models): here: https://thepihut.com/blogs/raspberry-pi-tutorials/27968772-turning-on-an-led-with-your-raspberry-pis-gpio-pins
  

*/


#include <stdio.h> // for standard in/out
#include <wiringPi.h> //wiring pi module
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "interrupt.h"
#include "soundplay.c"

/*
 ***************************************************************************
 * interrupts
 ***************************************************************************
 */

void interrupt () {
  pinNum = 0;
  causeAndEffect (pinNum);
}



/*
 ***************************************************************************
 * functions
 ***************************************************************************
 */

void causeAndEffect (int pinNum) {
  cause = digitalRead (pinNum);
  if (cause == HIGH){ //interrupt was a pressed down
    digitalWrite(OUT_PIN, HIGH);
    printf ("button pressed\n");
  }
  else { //interrupt was a depress?
    digitalWrite(OUT_PIN, LOW);
    printf ("button de-pressed\n");
    //playSound method
    play ();
  }
  effect = digitalRead (OUT_PIN);
  printf ("Pin 0 value: %d \nPin 1 value: %d\n\n", cause, effect);
  delay(1000);
}


/*
 *********************************************************************************
 * main
 *********************************************************************************
 */

int main (void) {

  //SETUP
  wiringPiSetup ();

  //PIN MODES
  pinMode (IN_PIN, OUTPUT) ; //May need this and line below so value doesn't stay as 1 when in input mode
  digitalWrite (IN_PIN, LOW);
  pinMode (IN_PIN, INPUT) ; //pin 0 gets input
  pinMode (OUT_PIN, OUTPUT) ; //pin 1 sets output


  //ATTACH FUNCTIONS TO INTERRUPTS
  //CANNOT ATTACH MULTIPLE INTERRUPTS PER PIN. Use one edgeType. Check if high or low in interrupt for "rising" and "falling" action. OR seperate buttons for each edgeType.
  wiringPiISR (0, INT_EDGE_BOTH, &interrupt);
  
  
  //LOOP - to keep program alive
  printf ("Waiting ... \n") ; fflush (stdout) ;
  for (;;) {
  }

  return 0 ;
} //main





















