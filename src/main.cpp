#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S_kbv.h>
#include <SPI.h>
#include "pins.hpp"
#include "ui.hpp"

// Initialize TFT
Adafruit_ST7796S_kbv tft(TFT_CS, TFT_DC, TFT_RST); // Matches pins.hpp

// System state
float voltage = 24.32; // Base dummy data
float current = 2.1;   // Base dummy data (100mA)
bool isCV = true;
bool loadOn = false;
bool protectOVP = false;
bool protectOCP = false;
bool protectOTP = false;
volatile int currentPage = 0;
volatile int lastCLK = 1;
const int encSwPin = PB8; // Rotary switch pin set to PB8

// Timing for fixed updates
unsigned long lastUpdate = 0;

void checkEncoder() {
  int clkState = digitalRead(ENC_CLK);
  if (clkState != lastCLK) {
    // No page change, keep on Main view (page 0)
    ui::drawPage(currentPage, voltage, current, isCV, loadOn, protectOVP, protectOCP, protectOTP);
  }
  lastCLK = clkState;
}

void checkSwitch() {
  if (digitalRead(encSwPin) == LOW) { // Assuming active LOW switch
    delay(50); // Debounce
    if (digitalRead(encSwPin) == LOW) {
      // No action, keep on Main view
      ui::drawPage(currentPage, voltage, current, isCV, loadOn, protectOVP, protectOCP, protectOTP);
    }
  }
}

void setup() {
  // Init SPI
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  // Initialize TFT
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ST7796S_BLACK); // Initial full clear

  // Encoder and Switch
  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);
  pinMode(encSwPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENC_CLK), checkEncoder, CHANGE);

  // Initial UI
  ui::drawPage(currentPage, voltage, current, isCV, loadOn, protectOVP, protectOCP, protectOTP);
}

void loop() {
  unsigned long currentTime = millis();

  // Add floating effect: ±30mV (0.03V) for voltage, ±3mA (0.003A) for current
  voltage = 32.32 + (random(-30, 31) / 1000.0); // ±0.03V
  current = 10.1 + (random(-3, 4) / 1000.0);     // ±0.003A

  // Update UI at fixed interval (default 500ms)
  if (currentTime - lastUpdate >= 500) {
    ui::drawPage(currentPage, voltage, current, isCV, loadOn, protectOVP, protectOCP, protectOTP);
    lastUpdate = currentTime;
  }

  checkSwitch(); // Check for rotary switch press
}