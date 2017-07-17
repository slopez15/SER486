/*
File: interrupt.h
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


#ifndef INTERRUPT_H_
#define INTERRUPT_H_



//which pin is getting input and setting output
#define	IN_PIN		0
#define	OUT_PIN		1

//gloabal vars
int pinNum;
int cause, effect;


//methods
void interrupt ();
void causeAndEffect (int pinNum);



#endif // INTERRUPT_H_

















