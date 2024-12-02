#include "Components/Display/Api/Display.h"
#include "ArduinoStandardLibrary.h"

Display::Display(int address, int columns, int rows)
    : lcd(address, columns, rows), columns(columns), rows(rows) {}

void Display::init() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
   // lcd.setCursor(0, 0);
}

void Display::on() {
    lcd.display();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void Display::off() {
    lcd.noDisplay();
    lcd.noBacklight();
    lcd.clear();
}

void Display::write(String message) {
    this->currentMessage = message;
}

void Display::clear() {
    lcd.clear();
    this->currentMessage = "";
}

void Display::update() {
    const char *wewe = this->currentMessage.c_str();
    lcd.setCursor(0, 0);
    lcd.print("Dio santo");
}