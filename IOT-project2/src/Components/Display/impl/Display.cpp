#include "Components/Display/Api/Display.h"

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

void Display::write(const char* message) {
    strncpy(currentMessage, message, sizeof(currentMessage) - 1);
    currentMessage[sizeof(currentMessage) - 1] = '\0';
}

void Display::clear() {
    lcd.clear();
    previousMessage[0] = '\0';
}

void Display::update() {
    if (strcmp(currentMessage, previousMessage) != 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(currentMessage);

        strncpy(previousMessage, currentMessage, sizeof(previousMessage) - 1);
        previousMessage[sizeof(previousMessage) - 1] = '\0';
    }
}
