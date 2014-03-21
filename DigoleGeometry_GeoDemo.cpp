/* *********************************************************************************** */
/* Digole Serial Display Library - Version 006                                         */
/* Copyright 2014 Timothy Brown / Paul Kourany / Digole                                */
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
#define _Digole_Serial_UART_

/* Be sure to #include "DigoleSerialDisp.h" *after* the #define above or your compile will fail. */

#include "DigoleSerialDisp.h"

/* Below are sane defaults for the various interfaces. Uncomment one and customize as needed! */

//DigoleSerialDisp digole(A2); //SPI
//DigoleSerialDisp digole(D4, D3, D2); //SoftSPI
//DigoleSerialDisp digole(0x27); //I2C
DigoleSerialDisp digole(115200); //UART


//Colours defined as 8-bit value RRRG GGBB
#define VGA_BLACK   0x00
#define VGA_WHITE   0x01
#define VGA_BLUE    0x03
#define VGA_DARKRED 0x20

#define VGA_RED     0xE0
#define VGA_GREEN   0x1C
#define VGA_LIME    0x14
#define VGA_YELLOW  0xFC

const int max_x = 160;	//screen width in pixels
const int max_y = 128;	//screen Hight in pixels


int random(int maxRand) {
    return rand() % maxRand;
}


/* *********************************************************************************** */
/* THIS DEMO IS WRITTEN FOR THE DIGOLE COLOR OLED 160x128                              */
/* *********************************************************************************** */

 
void setup() {
  digole.begin(OLED160x128);  //Set display to color OLED 160x128
  digole.backLightOn();
  digole.setColor(1);
}
 
void loop() {

  int x1,x2,x3,y1,y2,y3,r,as,ae;

  digole.clearScreen(); //CLear screen
  digole.disableCursor();

// Draw some random triangles
  for (int i=0; i<50; i++)
  { 
    digole.setTrueColor(random(255), random(255), random(255));
    x1=random(max_x);
    y1=random(max_y);
    x2=random(max_x);
    y2=random(max_y);
    digole.drawRoundRect(x1, y1, x2, y2);
    delay(10);
  }

  delay(1000);
  digole.clearScreen(); //CLear screen

// Draw some random triangles
  for (int i=0; i<50; i++)
  {
    digole.setTrueColor(random(255), random(255), random(255));
    x1=random(max_x);
    y1=random(max_y);
    x2=random(max_x);
    y2=random(max_y);
    digole.fillRoundRect(x1, y1, x2, y2);
    delay(15);
  }

  delay(1000);
  digole.clearScreen(); //CLear screen

// Draw some random triangles
  for (int i=0; i<50; i++)
  {
    digole.setTrueColor(random(255), random(255), random(255));
    x1=random(max_x);
    y1=random(max_y);
    x2=random(max_x);
    y2=random(max_y);
    x3=random(max_x);
    y3=random(max_y);
    digole.drawTriangle(x1, y1, x2, y2, x3, y3);
  }

  delay(1000);
  digole.clearScreen(); //CLear screen

// Draw some random filled triangles
  for (int i=0; i<50; i++)
  {
    digole.setTrueColor(random(255), random(255), random(255));
    x1=random(max_x);
    y1=random(max_y);
    x2=random(max_x);
    y2=random(max_y);
    x3=random(max_x);
    y3=random(max_y);
    digole.fillTriangle(x1, y1, x2, y2, x3, y3);
    delay(15);
  }

  delay(1000);
  digole.clearScreen(); //CLear screen

// Draw some random pies
  for (int i=0; i<50; i++)
  {
    digole.setTrueColor(random(255), random(255), random(255));
    x1=30+random(max_x-60);
    y1=30+random(max_y-60);
    r=10+random(20);
    as=random(360);
    ae=random(360);    digole.drawPie(x1, y1, r, as, ae);
    delay(10);
  }

  delay(1000);
  digole.clearScreen(); //CLear screen

//Draw a VU style meter and moving needle
  digole.setColor(VGA_BLUE);
  digole.drawFrame(0, 0, 160, 128);

  digole.setColor(VGA_LIME);
  digole.drawArc(80,128,108,-40,40,3);
  for (int i=-40; i<=40; i+=8)
    digole.drawArc(80,128,103,i,i,5);

  int l = 0;
  for (int i=0; i>=-40; i-=1)
  {
    digole.setColor(VGA_BLACK);
    digole.drawArc(80,128,55,l,l,75);
    l=i;
    digole.setColor(VGA_YELLOW);
    digole.drawArc(80,128,55,i,i,75);
    delay(40-abs(i));
  }

  for (int i=-40; i<=40; i+=1)
  {
    digole.setColor(VGA_BLACK);
    digole.drawArc(80,128,55,l,l,75);
    l=i;
    digole.setColor(VGA_YELLOW);
    digole.drawArc(80,128,55,i,i,75);
    delay(40-abs(i));
  }

  for (int i=40; i>=0; i-=1)
  {
    digole.setColor(VGA_BLACK);
    digole.drawArc(80,128,55,l,l,75);
    l=i;
    digole.setColor(VGA_YELLOW);
    digole.drawArc(80,128,55,i,i,75);
    delay(40-i);
  }

  delay(1000);
  digole.clearScreen(); //CLear screen
  
// Draw some random ellipses
  for (int i=0; i<50; i++)
  {
    digole.setTrueColor(random(255), random(255), random(255));
    x1=20+random(max_x-20);
    y1=20+random(max_y-20);
    x2=5+random(30);
    y2=5+random(30);
    digole.drawEllipse(x1, y1, x2, y2);
    delay(100);
  }

  delay(1000);
  digole.clearScreen(); //CLear screen
  
// Draw some random filled ellipses
  for (int i=0; i<50; i++)
  {
    digole.setTrueColor(random(255), random(255), random(255));
    x1=20+random(max_x-20);
    y1=20+random(max_y-20);
    x2=5+random(30);
    y2=5+random(30);
    digole.drawFilledEllipse(x1, y1, x2, y2);
    delay(100);
  }

}
