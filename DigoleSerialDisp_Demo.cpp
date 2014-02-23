/* *********************************************************************************** */
/* Digole Serial Display Library - Version 005 - Copyright 2014 Timothy Brown / Digole */
/* *********************************************************************************** */
/* Setup the class for your display *before* void setup():                             */
/*                                                                                     */
/* DigoleSerialDisp digole(arguments);                                                 */
/*                                                                                     */
/* Arguments:                                                                          */
/*                                                                                     */
/* [SPI] Chip Select Pin (SS for the default pin, 255 if CS is hardwired low.)         */
/* [SoftSPI] Data Pin, Clock Pin, Chip Select Pin (255 if CS is hardwired low.)        */
/* [I2C] Address of the Display (Default: 0x27)                                        */
/* [UART] Baud Rate [9600 to 115200]                                                   */
/*                                                                                     */
/* To use, call digole.begin(); *inside* void setup(); (or loop) to start the display. */
/* You may also call digole.end(); to release the pins and clear the I2C/SPI/UART bus. */
/*                                                                                     */
/* Change XXXX in the #define below to the desired interface: SPI, SoftSPI, I2C, UART. */
/* *********************************************************************************** */

#define _Digole_Serial_XXXX_

#include "DigoleSerialDisp.h"

DigoleSerialDisp digole(arguments);

void setup() {
	
	digole.begin();

}

void loop() {

}