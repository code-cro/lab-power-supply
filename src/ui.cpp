#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S_kbv.h>
#include <font_small.h> 
#include <font_large.h>
#include "pins.hpp"
#include "ui.hpp"

extern Adafruit_ST7796S_kbv tft;

namespace ui
{
  void drawPage(int page, float voltage, float current, bool isCV, bool loadOn, bool protectOVP, bool protectOCP, bool protectOTP)
  {
    static int currentPage = 0; // Track page state internally
    currentPage = page;         // Only Main view (page 0)
    drawMainView(voltage, current, isCV, loadOn, protectOVP, protectOCP, protectOTP);
    return; // Propagate updated page
  }

  void drawMainView(float voltage, float current, bool isCV, bool loadOn, bool protectOVP, bool protectOCP, bool protectOTP)
  {
    static float lastVoltage = -1.0;
    static float lastCurrent = -1.0;
    static bool lastIsCV = false;
    static bool lastLoadOn = false;
    static bool lastProtectOVP = false;
    static bool lastProtectOCP = false;
    static bool lastProtectOTP = false;

    tft.setFont(&FontLarge);
    tft.setTextSize(1);

    // Voltage (partial fill only if changed)
    if (voltage != lastVoltage)
    {
      tft.fillRect(120, 28, 200, 56, ST7796S_BLACK); // Clear only voltage area
      tft.setTextColor(ST7796S_WHITE);
      tft.setCursor(120, 80);
      tft.print(voltage, 3);
      tft.setCursor(310, 80);
      tft.print(" V");
      lastVoltage = voltage;
    }

    // Current (partial fill only if changed)
    if (current != lastCurrent)
    {
      tft.fillRect(120, 100, 200, 56, ST7796S_BLACK); // Clear only current area
      tft.setTextColor(ST7796S_WHITE);
      tft.setCursor(120, 150);
      tft.print(current, 3);
      tft.setCursor(310, 150);
      tft.print(" A");
      lastCurrent = current;
    }

    // Power (partial fill only if changed)
    tft.fillRect(120, 190, 200, 38, ST7796S_BLACK); // Clear only power area
    tft.setTextColor(ST7796S_GREENYELLOW);
    tft.setTextSize(1);
    tft.setCursor(120, 220);
    tft.print(voltage * current, 3);
    tft.setCursor(310, 220);
    tft.print(" W");

    // Indicators (CC/CV and others) - partial update if status changed
    if (isCV != lastIsCV || loadOn != lastLoadOn || protectOVP != lastProtectOVP || protectOCP != lastProtectOCP || protectOTP != lastProtectOTP)
    {
      tft.setFont(&FontSmall);
      tft.setTextSize(1);
      tft.fillRect(60, 300 - 72, 480, 72, ST7796S_BLACK); // Clear only indicator area
      tft.setTextColor(isCV ? ST7796S_GREEN : ST7796S_RED);
      tft.setCursor(60, 300);
      tft.print("CV ");
      tft.setTextColor(!isCV ? ST7796S_GREEN : ST7796S_RED);
      tft.print("CC ");
      tft.setTextColor(protectOVP ? ST7796S_RED : ST7796S_GREEN);
      tft.print("OVP ");
      tft.setTextColor(protectOCP ? ST7796S_RED : ST7796S_GREEN);
      tft.print("OCP ");
      tft.setTextColor(protectOTP ? ST7796S_RED : ST7796S_GREEN);
      tft.print("OTP ");
      tft.setTextColor(loadOn ? ST7796S_GREEN : ST7796S_RED);
      tft.print("OUT");
      lastIsCV = isCV;
      lastLoadOn = loadOn;
      lastProtectOVP = protectOVP;
      lastProtectOCP = protectOCP;
      lastProtectOTP = protectOTP;
    }
  }
}