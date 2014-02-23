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
/* *********************************************************************************** */

/* Uncomment the #define below for the desired interface: SPI, SoftSPI, I2C, UART. */

//#define _Digole_Serial_SPI_
//#define _Digole_Serial_SoftSPI_
//#define _Digole_Serial_I2C_
//#define _Digole_Serial_UART_

/* Be sure to #include "DigoleSerialDisp.h" *after* the #define above or your compile will fail. */

#include "DigoleSerialDisp.h"

/* Below are sane defaults for the various interfaces. Uncomment one and customize as needed! */

//DigoleSerialDisp digole(A2); //SPI
//DigoleSerialDisp digole(D4, D3, D2); //SoftSPI
//DigoleSerialDisp digole(0x27); //I2C
//DigoleSerialDisp digole(115200); //UART

void setup() {
	
	digole.begin();
	delay(500);
	digole.clearScreen;
	delay(50);
	digole.print("Hello World!");

}

void loop() {

}