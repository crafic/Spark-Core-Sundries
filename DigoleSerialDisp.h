/* *********************************************************************************** */
/* Digole Serial Display Library - Version 006					       */
/* Copyright 2014 Timothy Brown / Paul Kourany / Digole 			       */
/* *********************************************************************************** */

// **********************
// * DigoleSerialDisp.h *
// **********************

#ifndef DigoleSerialDisp_h
#define DigoleSerialDisp_h

#define _TEXT_ 0
#define _GRAPH_ 1

enum displayDims { OLED160x128, OLED96x64, LCD128x64 };


class DigoleSerialDisp : public Print {
public:

//
// UART/I2C/SoftSPI/SPI Functions
//
#if defined(_Digole_Serial_UART_)

DigoleSerialDisp(unsigned long baud) //UART set up
    {
        _Baud = baud;
        _Comdelay=0;
    }

    void begin(displayDims size) {
        Serial1.begin(9600);
        Serial1.print("SB");
        Serial1.println(_Baud);
        delay(100);
        Serial1.begin(_Baud);
        
        setDisplaySize(size);
    }

    void end(void) {
    }

    size_t write(uint8_t value) {
        Serial1.write(value);
        return 1;
    }
#endif
#if defined(_Digole_Serial_I2C_)
    DigoleSerialDisp(uint8_t add)
    {
        _I2Caddress = add;
        _Comdelay=10;
    }

	void begin(displayDims size) {
		Wire.begin();
        
        setDisplaySize(size);
    }

    void end(void) {
    }

    size_t write(uint8_t value) {
        Wire.beginTransmission(_I2Caddress);
        Wire.write(value);
        Wire.endTransmission();
        return 1;
    }
#endif
#if defined(_Digole_Serial_SPI_)
    DigoleSerialDisp(uint8_t pinSS) {
        
        _Comdelay = 10;
        _SS = pinSS;
        
	}
    
    void begin(displayDims size) {
        
        pinMode(_SS, OUTPUT);
        digitalWrite(_SS, HIGH);
        SPI.setBitOrder(MSBFIRST);
        SPI.setClockDivider(SPI_CLOCK_DIV32);
        SPI.setDataMode(1);
        SPI.begin();

        setDisplaySize(size);
    }
    
    void end(void) {
        pinMode(_SS, INPUT);
        SPI.end();
    }

    size_t write(uint8_t value) {
        
        PIN_MAP[_SS].gpio_peripheral->BRR = PIN_MAP[_SS].gpio_pin; //Low
        //delayMicroseconds(1); *Upped SPI_CLOCK_DIV to 32 and removed CS delay*
        SPI.transfer(value);
        //delayMicroseconds(1);
        PIN_MAP[_SS].gpio_peripheral->BSRR = PIN_MAP[_SS].gpio_pin; //High
        return 1;
    }
#endif

#if defined(_Digole_Serial_SoftSPI_)
    DigoleSerialDisp(uint8_t pinData, uint8_t pinClock, uint8_t pinSS) {
        
        _Comdelay = 5;
        
        _Clock = pinClock;
        _Data = pinData;
        _SS = pinSS;
        
    }
    
    void begin(displayDims size) {
        
        pinMode(_Clock, OUTPUT);
        pinMode(_Data, OUTPUT);
        pinMode(_SS, OUTPUT);
        digitalWrite(_Clock, LOW);
        digitalWrite(_Data, LOW);
        digitalWrite(_SS, HIGH);
        
        setDisplaySize(size);
    }
    
    void end(void) {
        pinMode(_Clock, INPUT);
        pinMode(_Data, INPUT);
        pinMode(_SS, INPUT);
    }

    size_t write(uint8_t value) {
        
        PIN_MAP[_SS].gpio_peripheral->BRR = PIN_MAP[_SS].gpio_pin; //Low
        shiftOut(_Data, _Clock, MSBFIRST, value);
        PIN_MAP[_SS].gpio_peripheral->BSRR = PIN_MAP[_SS].gpio_pin; //High
        return 1;
    }
#endif

    //
    // Print Functions
    //

    void println(const String &v) {
        preprint();
        Print::println(v);
        Print::println("TRT");
    }

    void println(const char v[]) {
        preprint();
        Print::println(v);
        Print::println("TRT");
    }

    void println(char v) {
        preprint();
        Print::println(v);
        Print::println("TRT");
    }

    void println(unsigned char v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("TRT");
    }

    void println(int v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("TRT");
    }

    void println(unsigned int v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("TRT");
    }

    void println(long v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("TRT");
    }

    void println(unsigned long v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("TRT");
    }

    void println(double v, int base = 2) {
        preprint();
        Print::println(v, base);
        Print::println("TRT");
    }

    void println(const Printable& v) {
        preprint();
        Print::println(v);
        Print::println("TRT");
    }

    void println(void) {
        Print::println("TRT");
    }


    void print(const String &v) {
        preprint();
        Print::println(v);
    }

    size_t print(const char v[]) {
        preprint();
        Print::println(v);
    }

    void print(char v) {
        preprint();
        Print::println(v);
    }

    void print(unsigned char v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    void print(int v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    void print(unsigned int v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    void print(long v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    void print(unsigned long v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    void print(double v, int base = 2) {
        preprint();
        Print::println(v, base);
    }

    void print(const Printable& v) {
        preprint();
        Print::println(v);
    }
    
    //
    // Text LCD Adapter Functions
    //

    void disableCursor(void) {
        Print::print("CS0");
    }

    void enableCursor(void) {
        Print::print("CS1");
    }

    void drawStr(uint8_t x, uint8_t y, const char *s) {
        Print::print("TP");
        write(x);
        write(y);
        Print::print("TT");
        Print::println(s);
    }

    void setPrintPos(uint8_t x, uint8_t y, uint8_t graph = _TEXT_) {
        if (graph == false) {
            Print::print("TP");
            write(x);
            write(y);
        } else {
            Print::print("GP");
            write(x);
            write(y);
        }
    }

    void clearScreen(void) {
        Print::print("CL");
    }

    void setLCDColRow(uint8_t col, uint8_t row) {
        Print::print("STCR");
        write(col);
        write(row);
        Print::print("\x80\xC0\x94\xD4");
    }

    void setI2CAddress(uint8_t add) {
        Print::print("SI2CA");
        write(add);
        _I2Caddress = add;
    }

    void displayConfig(uint8_t v) {
        Print::print("DC");
        write(v);
    }
    
    void displayStartScreen(uint8_t m) {
        Print::print("DSS");
        write(m);
    } //display start screen

    void setMode(uint8_t m) {
        Print::print("DM");
        write(m);
    } //set display mode

    void setTextPosBack(void) {
        Print::print("ETB");
    } //set text position back to previous, only one back allowed

    void setTextPosOffset(char xoffset, char yoffset) {
        Print::print("ETO");
        write(xoffset);
        write(yoffset);
    }

    void setTextPosAbs(uint8_t x, uint8_t y) {
        Print::print("ETP");
        write(x);
        write(y);
    }
    void setLinePattern(uint8_t pattern) {
        Print::print("SLP");
        write(pattern);
    }
    void setLCDChip(uint8_t chip) {      //only for universal LCD adapter
        Print::print("SLCD");
        write(chip);
    }
     
     void digitalOutput(uint8_t x) {
         Print::print("DOUT");
         write(x);
    }
    
    void preprint(void);

	//
	// Graphic LCD/OLED Adapter Functions (U8GLIB Compatible)
	//

    void drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap);
    void drawBitmap256(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap);
    void drawBitmap262K(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap);
    void setTrueColor(uint8_t r, uint8_t g, uint8_t b);
    void setRot90(void);
    void setRot180(void);
    void setRot270(void);
    void undoRotation(void);
    void setRotation(uint8_t);
    void setContrast(uint8_t);
    void drawBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    void drawCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t = 0);
    void drawDisc(uint8_t x, uint8_t y, uint8_t r);
    void drawFrame(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    void drawPixel(uint8_t x, uint8_t y, uint8_t = 1);
    void drawLine(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1);
    void drawLineTo(uint8_t x, uint8_t y);
    void drawHLine(uint8_t x, uint8_t y, uint8_t w);
    void drawVLine(uint8_t x, uint8_t y, uint8_t h);
    void drawRoundRect(int x1, int y1, int x2, int y2);
    void fillRoundRect(int x1, int y1, int x2, int y2);
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
    void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
    void drawArc(int x, int y, int r, int startAngle, int endAngle, int thickness);
    void drawPie(int x, int y, int r, int startAngle, int endAngle);
    void drawEllipse(int CX, int CY, int XRadius, int YRadius);
    void drawFilledEllipse(int CX, int CY, int XRadius, int YRadius);

	//
	// Graphic LCD/OLED Adapter Functions (Special Functions)
	//

    void setDisplaySize(displayDims size);  //set display dimmensions: OLED160x128, OLED96x64, LCD128x64
    void setFont(uint8_t font); //set font, availale: 6,10,18,51,120,123, user font: 200-203
    void nextTextLine(void); //got to next text line, depending on the font size
    void setColor(uint8_t); //set color for graphic function
    void backLightOn(void); //Turn on back light
    void backLightOff(void); //Turn off back light
    void setScreenOn(void);  //Turn screen on 
    void setScreenOff(void); //Turn screen off to save power
    void directCommand(uint8_t d); //send command to LCD drectly
    void directData(uint8_t d); //send data to LCD drectly
    void moveArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char xoffset, char yoffset); //move a area of screen to another place
    void uploadStartScreen(int lon, const unsigned char *data); //upload start screen
    void uploadUserFont(int lon, const unsigned char *data, uint8_t sect); //upload user font

private:
	uint8_t _I2Caddress;
	uint8_t _Baud;
	uint8_t _Clock;
	uint8_t _Data;
	uint8_t _SS;
	uint8_t _Comdelay;

    	int _max_x;
    	int _max_y;
    
    	void plotEllipse(int CX, int CY, int XRadius, int YRadius, int fill);
    	void plot4EllipsePoints(int CX, int CY, int X, int Y, int fill);

};

#endif
