#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S_kbv.h>
#include "pins.hpp" // Use provided pin definitions

// TFT pins from pins.hpp
#define TFT_CS  PA4
#define TFT_DC  PA2
#define TFT_RST PA1

// Button pins from pins.hpp
#define BTN_SET  PB5  // Set voltage/current
#define BTN_FINE PB4  // Fine/rough toggle
#define BTN_OUT  PB3  // Output enable/disable

// TFT instance
Adafruit_ST7796S_kbv tft = Adafruit_ST7796S_kbv(TFT_CS, TFT_DC, TFT_RST);

// Button arrays
const uint8_t buttons[] = {BTN_SET, BTN_FINE, BTN_OUT};
const char* buttonNames[] = {"SET", "FINE", "OUT"};

bool buttonStates[3] = {false, false, false};
bool lastButtonStates[3] = {false, false, false};

const unsigned long debounceDelay = 30;
unsigned long lastDebounceTimes[3] = {0, 0, 0};

void setup() {
  // Initialize button pins as INPUT_PULLUP (per pins.hpp usage)
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_FINE, INPUT_PULLUP);
  pinMode(BTN_OUT, INPUT_PULLUP);

  // Initialize TFT
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ST7796S_BLACK);
  tft.setTextColor(ST7796S_WHITE);
  tft.setCursor(20, 30);
  tft.println("Button Test");
}

void loop() {
  bool updated = false;

  // Check button states
  for (int i = 0; i < 3; i++) {
    bool reading = digitalRead(buttons[i]) == LOW; // Active LOW

    if (reading != lastButtonStates[i]) {
      lastDebounceTimes[i] = millis();
    }

    if ((millis() - lastDebounceTimes[i]) > debounceDelay) {
      if (reading != buttonStates[i]) {
        buttonStates[i] = reading;
        updated = true; // Mark for display update
      }
    }

    lastButtonStates[i] = reading;
  }

  // Update TFT display if any button state changed
  if (updated) {
    tft.fillRect(20, 50, 440, 150, ST7796S_BLACK); // Clear display area
    tft.setTextSize(1);

    for (int i = 0; i < 3; i++) {
      tft.setCursor(20, 80 + i * 40);
      tft.setTextColor(buttonStates[i] ? ST7796S_GREEN : ST7796S_RED);
      tft.print(buttonNames[i]);
      tft.print(": ");
      tft.print(buttonStates[i] ? "PRESSED" : "RELEASED");
    }
  }

  delay(10);
}