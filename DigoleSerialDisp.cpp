//
// Digole.h
//

class DigoleSerialDisp : public Print {
public:

//
// UART/I2C/SPI Functions
//

#if defined(_Digole_Serial_SPI_)
    DigoleSerialDisp(uint8_t pinSS) {
        
        _Comdelay = 10;
        _SS = pinSS;
        
    }
    
    void begin(void) {
        
        pinMode(_SS, OUTPUT);
        digitalWrite(_SS, HIGH);
        SPI.setBitOrder(MSBFIRST);
        SPI.setClockDivider(SPI_CLOCK_DIV64);
        SPI.setDataMode(0);
        SPI.begin();
        
    }
    
    void end(void) {
        pinMode(_SS, INPUT);
        SPI.end();
    }

    size_t write(uint8_t value) {
        
        PIN_MAP[_SS].gpio_peripheral->BRR = PIN_MAP[_SS].gpio_pin; //Low
        SPI.setDataMode(3);
        SPI.transfer(value);
        SPI.setDataMode(0);
        PIN_MAP[_SS].gpio_peripheral->BSRR = PIN_MAP[_SS].gpio_pin; //High
        return 1;
    }
#endif

#if defined(_Digole_Serial_SoftSPI_)
    DigoleSerialDisp(uint8_t pinData, uint8_t pinClock, uint8_t pinSS) {
        
        _Comdelay = 1;
        
        _Clock = pinClock;
        _Data = pinData;
        _SS = pinSS;
        
    }
    
    void begin(void) {
        
        pinMode(_Clock, OUTPUT);
        pinMode(_Data, OUTPUT);
        pinMode(_SS, OUTPUT);
        digitalWrite(_Clock, LOW);
        digitalWrite(_Data, LOW);
        digitalWrite(_SS, HIGH);
        
    }
    
    void end(void) {
        pinMode(_Clock, INPUT);
        pinMode(_Data, INPUT);
        pinMode(_SS, INPUT);
    }

    size_t write(uint8_t value) {
        
        PIN_MAP[_SS].gpio_peripheral->BRR = PIN_MAP[_SS].gpio_pin; //Low
        delayMicroseconds(1);
        shiftOut(_Data, _Clock, MSBFIRST, value);
        delayMicroseconds(1);
        PIN_MAP[_SS].gpio_peripheral->BSRR = PIN_MAP[_SS].gpio_pin; //High
        return 1;
    }
#endif

    //
    // Print Functions
    //

    size_t println(const String &v) {
        preprint();
        Print::println(v);
        Print::println("\x0dTRT");
    }

    size_t println(const char v[]) {
        preprint();
        Print::println(v);
        Print::println("\x0dTRT");
    }

    size_t println(char v) {
        preprint();
        Print::println(v);
        Print::println("\x0dTRT");
    }

    size_t println(unsigned char v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("\x0dTRT");
    }

    size_t println(int v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("\x0dTRT");
    }

    size_t println(unsigned int v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("\x0dTRT");
    }

    size_t println(long v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("\x0dTRT");
    }

    size_t println(unsigned long v, int base = DEC) {
        preprint();
        Print::println(v, base);
        Print::println("\x0dTRT");
    }

    size_t println(double v, int base = 2) {
        preprint();
        Print::println(v, base);
        Print::println("\x0dTRT");
    }

    size_t println(const Printable& v) {
        preprint();
        Print::println(v);
        Print::println("\x0dTRT");
    }

    size_t println(void) {
        Print::println("\x0dTRT");
    }


    size_t print(const String &v) {
        preprint();
        Print::println(v);
    }

    size_t print(const char v[]) {
        preprint();
        Print::println(v);
    }

    size_t print(char v) {
        preprint();
        Print::println(v);
    }

    size_t print(unsigned char v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    size_t print(int v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    size_t print(unsigned int v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    size_t print(long v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    size_t print(unsigned long v, int base = DEC) {
        preprint();
        Print::println(v, base);
    }

    size_t print(double v, int base = 2) {
        preprint();
        Print::println(v, base);
    }

    size_t print(const Printable& v) {
        preprint();
        Print::println(v);
    }
    
    //
    // Header Functions
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

    void setPrintPos(uint8_t x, uint8_t y, bool graph = false) {
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
    /*----------Functions for Graphic LCD/OLED adapters only---------*/
    //the functions in this section compatible with u8glib
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
    //-------------------------------
    //special functions for our adapters
    void setFont(uint8_t font); //set font, availale: 6,10,18,51,120,123, user font: 200-203
    void nextTextLine(void); //got to next text line, depending on the font size
    void setColor(uint8_t); //set color for graphic function
    void backLightOn(void); //Turn on back light
    void backLightOff(void); //Turn off back light
    void directCommand(uint8_t d); //send command to LCD drectly
    void directData(uint8_t d); //send data to LCD drectly
    void moveArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char xoffset, char yoffset); //move a area of screen to another place
    void uploadStartScreen(int lon, const unsigned char *data); //upload start screen
    void uploadUserFont(int lon, const unsigned char *data, uint8_t sect); //upload user font

private:
    uint8_t _I2Caddress;
    uint8_t _Clock;
    uint8_t _Data;
    uint8_t _SS;
    uint8_t _Comdelay;

};

//
// Digole.cpp
//

void DigoleSerialDisp::preprint(void) {
    //write((uint8_t)0);
    Print::print("TT");
}

/*----------Functions for Graphic LCD/OLED adapters only---------*/
void DigoleSerialDisp::drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap) {
    uint8_t i = 0;
    if ((w & 7) != 0)
        i = 1;
    Print::print("DIM");
    write(x);
    write(y);
    write(w);
    write(h);
    for (int j = 0; j < h * ((w >> 3) + i); j++) {
        write(bitmap[j]);
    }
}

void DigoleSerialDisp::setRot90(void) {
    Print::print("SD1");
}

void DigoleSerialDisp::setRot180(void) {
    Print::print("SD2");
}

void DigoleSerialDisp::setRot270(void) {
    Print::print("SD3");
}

void DigoleSerialDisp::undoRotation(void) {
    Print::print("SD0");
}

void DigoleSerialDisp::setRotation(uint8_t d) {
    Print::print("SD");
    write(d);
}

void DigoleSerialDisp::setContrast(uint8_t c) {
    Print::print("CT");
    write(c);
}

void DigoleSerialDisp::drawBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    Print::print("FR");
    write(x);
    write(y);
    write(x + w);
    write(y + h);
}

void DigoleSerialDisp::drawCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t f) {
    Print::print("CC");
    write(x);
    write(y);
    write(r);
    write(f);
}

void DigoleSerialDisp::drawDisc(uint8_t x, uint8_t y, uint8_t r) {
    drawCircle(x, y, r, 1);
}

void DigoleSerialDisp::drawFrame(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    Print::print("DR");
    write(x);
    write(y);
    write(x + w);
    write(y + h);
}

void DigoleSerialDisp::drawPixel(uint8_t x, uint8_t y, uint8_t color) {
    Print::print("DP");
    write(x);
    write(y);
    write(color);
}

void DigoleSerialDisp::drawLine(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1) {
    Print::print("LN");
    write(x);
    write(y);
    write(x1);
    write(y1);
}

void DigoleSerialDisp::drawLineTo(uint8_t x, uint8_t y) {
    Print::print("LT");
    write(x);
    write(y);
}

void DigoleSerialDisp::drawHLine(uint8_t x, uint8_t y, uint8_t w) {
    drawLine(x, y, x + w, y);
}

void DigoleSerialDisp::drawVLine(uint8_t x, uint8_t y, uint8_t h) {
    drawLine(x, y, x, y + h);
}

void DigoleSerialDisp::nextTextLine(void) {
    write((uint8_t) 0);
    Print::print("TRT");
}

void DigoleSerialDisp::setFont(uint8_t font) {
    Print::print("SF");
    write(font);
}

void DigoleSerialDisp::setColor(uint8_t color) {
    Print::print("SC");
    write(color);
}

void DigoleSerialDisp::backLightOn(void) {
    Print::print("BL");
    write((uint8_t) 1);
}

void DigoleSerialDisp::backLightOff(void) {
    Print::print("BL");
    write((uint8_t) 0);
}

void DigoleSerialDisp::directCommand(uint8_t d) {
    Print::print("MCD");
    write(d);
}

void DigoleSerialDisp::directData(uint8_t d) {
    Print::print("MDT");
    write(d);
}

void DigoleSerialDisp::moveArea(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, char xoffset, char yoffset) {
    Print::print("MA");
    write(x0);
    write(y0);
    write(w);
    write(h);
    write(xoffset);
    write(yoffset);
}

void DigoleSerialDisp::uploadStartScreen(int lon, const unsigned char *data) {
    Print::print("SSS");
    write((uint8_t) (lon % 256));
    write((uint8_t) (lon / 256));
    delay(300);
    for (int j = 0; j < lon; j++) {
        if((j%32)==0) {
            delay(50);
            delay(_Comdelay);
        }
         
        write(data[j]);
    }
}

void DigoleSerialDisp::uploadUserFont(int lon, const unsigned char *data, uint8_t sect) {
    Print::print("SUF");
    write(sect);
    write((uint8_t) (lon % 256));
    write((uint8_t) (lon / 256));
    for (int j = 0; j < lon; j++) {
        if((j%32)==0) {
            delay(50);
            delay(_Comdelay);
        }
         
        write(data[j]);
    }
}

void DigoleSerialDisp::drawBitmap256(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap) {
    Print::print("EDIM1");
    write(x);
    write(y);
    write(w);
    write(h);
    for (int j = 0; j < h * w; j++) {
        if((j%1024)==0) {
            delay(_Comdelay);
        }
        write(bitmap[j]);
    }
}

void DigoleSerialDisp::drawBitmap262K(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap) {
    Print::print("EDIM3");
    write(x);
    write(y);
    write(w);
    write(h);
    for (int j = 0; (j < h * w * 3); j++) {
        if((j%1024)==0) {
            delay(_Comdelay);
        }
        write(bitmap[j]);
    }
}

void DigoleSerialDisp::setTrueColor(uint8_t r, uint8_t g, uint8_t b) {	//Set true color
    Print::print("ESC");
    write(r); 
    write(g);
    write(b);
}

/* ************************** */
/* *** End Digole Library *** */
/* ************************** */