/*
  ============================================================
  Project Title : Arduino Rotary Encoder + LCD I2C Display
  GitHub Repository: github.com/alvindikapribadi/arduino-rotary-lcd-i2c-display
  YouTube Channel  : youtube.com/@AlvinPribadi
  Description   :
  This project demonstrates how to use a rotary encoder
  to control a counter value and display it on a 16x2
  LCD with I2C module. Rotate clockwise to increase value,
  counter-clockwise to decrease value, and press the button
  to reset the value to zero.

  ------------------------------------------------------------
  Components:
  - Arduino Uno
  - Rotary Encoder (CLK, DT, SW)
  - 16x2 LCD with I2C module (PCF8574)
  - Breadboard
  - Jumper wires

  ------------------------------------------------------------
  Wiring:

  Rotary Encoder:
  CLK  -> Pin 2
  DT   -> Pin 3
  SW   -> Pin 4
  VCC  -> 5V
  GND  -> GND

  LCD I2C:
  VCC  -> 5V
  GND  -> GND
  SDA  -> A4
  SCL  -> A5

  ------------------------------------------------------------
  Note:
  If the LCD does not display anything,
  scan the I2C address (usually 0x27 or 0x3F).
  ============================================================
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change address if needed (0x27 is common)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Rotary Encoder Pins
const int pinCLK = 2;
const int pinDT  = 3;
const int pinSW  = 4;

int counter = 0;
int lastCLKState;
bool lastButtonState = HIGH;

void setup() {
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinSW, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Rotary Value:");

  lastCLKState = digitalRead(pinCLK);
}

void loop() {
  int currentCLKState = digitalRead(pinCLK);

  // Detect rotation
  if (currentCLKState != lastCLKState && currentCLKState == HIGH) {
    if (digitalRead(pinDT) != currentCLKState) {
      counter++;   // Clockwise
    } else {
      counter--;   // Counter-clockwise
    }

    updateLCD();
  }

  lastCLKState = currentCLKState;

  // Button Press (Reset)
  bool buttonState = digitalRead(pinSW);

  if (buttonState == LOW && lastButtonState == HIGH) {
    counter = 0;
    updateLCD();
    delay(200); // Simple debounce
  }

  lastButtonState = buttonState;
}

void updateLCD() {
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear line
  lcd.setCursor(0, 1);
  lcd.print(counter);
}
