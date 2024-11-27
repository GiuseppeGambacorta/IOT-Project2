#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <LiquidCrystal_I2C.h>
//#include <cstring.h>

class Display {
private:
    LiquidCrystal_I2C lcd;
    char currentMessage[32] = ""; // Buffer per il messaggio corrente
    char previousMessage[32] = ""; // Buffer per il messaggio precedente
    int columns;
    int rows;

public:
    Display(int address, int columns, int rows);
    void init();
    void on();
    void off();
    void write(const char* message);
    void clear();
    void update();
};

#endif
