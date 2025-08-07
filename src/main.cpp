#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S_kbv.h>
#include "pins.hpp"
#include "ui.hpp"
#include "input.hpp"

// Fonts
#include <RobotoMono_Regular12pt7b.h>
#include <RobotoMono_Regular24pt7b.h>

// Display instance
Adafruit_ST7796S_kbv tft = Adafruit_ST7796S_kbv(TFT_CS, TFT_DC, TFT_RST);

// System state
int currentPage = 0;
const int totalPages = 2; // Main View (0), Input Test (1)
float voltage = 24.32; // Dummy data
float current = 2.1;   // Dummy data
bool isCV = true;
bool loadOn = false;
bool protectOVP = false;
bool protectOCP = false;
bool protectOTP = false;
int encoderPos = 0;
bool encBtnShort = false;
bool encBtnLong = false;
bool btnSet = false;
bool btnFine = false;
bool btnOut = false;

void setup() {
  // Initialize inputs
  input::init();

  // I2C Touch controller (for future use)
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize display
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ST7796S_BLACK);
  tft.setFont(&RobotoMono_Regular24pt7b);
  tft.setTextColor(ST7796S_WHITE);
  tft.setCursor(20, 30);
  tft.println("Starting...");

  delay(1000);
}

void loop() {
  // Poll inputs
  input::poll();
  input::Action action = input::getAction();

  // Process input actions
  switch (action) {
    case input::Action::RotateCW:
      currentPage = (currentPage + 1) % totalPages; // Circular increment
      break;
    case input::Action::RotateCCW:
      currentPage = (currentPage - 1 + totalPages) % totalPages; // Circular decrement
      break;
    case input::Action::Press:
      encBtnShort = true;
      break;
    case input::Action::LongPress:
      encBtnLong = true;
      break;
    case input::Action::Btn1:
      btnSet = true;
      break;
    case input::Action::Btn2:
      btnFine = true;
      break;
    case input::Action::Btn3:
      btnOut = true;
      break;
    default:
      break;
  }

  // Update button states based on pin readings
  btnSet = digitalRead(BTN_SET) == LOW || btnSet;
  btnFine = digitalRead(BTN_FINE) == LOW || btnFine;
  btnOut = digitalRead(BTN_OUT) == LOW || btnOut;

  // Reset button states if pins are released and no new action
  if (action != input::Action::Press) encBtnShort = false;
  if (action != input::Action::LongPress) encBtnLong = false;
  if (action != input::Action::Btn1 && digitalRead(BTN_SET) == HIGH) btnSet = false;
  if (action != input::Action::Btn2 && digitalRead(BTN_FINE) == HIGH) btnFine = false;
  if (action != input::Action::Btn3 && digitalRead(BTN_OUT) == HIGH) btnOut = false;

  // Update encoder position for Input Test Page
  if (currentPage == 1) {
    if (action == input::Action::RotateCW) encoderPos++;
    if (action == input::Action::RotateCCW) encoderPos--;
  }

  // Update display
  ui::drawPage(currentPage, voltage, current, isCV, loadOn, protectOVP, protectOCP, protectOTP, encoderPos, encBtnShort, encBtnLong, btnSet, btnFine, btnOut);

  delay(50);
}