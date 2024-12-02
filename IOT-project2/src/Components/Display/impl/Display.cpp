#include "Components/Display/Api/Display.h"
#include "ArduinoStandardLibrary.h"

Display::Display(int address, int columns, int rows)
    : lcd(address, columns, rows), columns(columns), rows(rows), currentMessage(""), oldMessage("") {}

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

void Display::write(const char* message) {
    this->currentMessage = message;
    
  
}

void Display::clear() {
    //lcd.clear();
    //this->currentMessage = "";
}

void Display::update() {

    if (strcmp(this->currentMessage, this->oldMessage) == 0) {
        return;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(this->currentMessage);
    this->oldMessage = this->currentMessage;


}
