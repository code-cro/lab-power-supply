#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S_kbv.h>
#include <RobotoMono_Regular12pt7b.h> 
#include <RobotoMono_Regular32pt7b.h> 
#include "pins.hpp"
#include "ui.hpp"

extern Adafruit_ST7796S_kbv tft;

namespace ui
{
  void setSmallFont(void) {
    tft.setFont(&RobotoMono_Regular12pt7b);
    // tft.setTextSize(1);
  }

  void setLargeFont(void) {
    tft.setFont(&RobotoMono_Regular32pt7b);
    // tft.setTextSize(1);
  }

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
    static float lastPower = -1.0;
    static float power = -1.0;
    static bool lastIsCV = false;
    static bool lastLoadOn = false;
    static bool lastProtectOVP = false;
    static bool lastProtectOCP = false;
    static bool lastProtectOTP = false;

    setLargeFont();

    // Voltage (partial fill only if changed)
    if (voltage != lastVoltage)
    {
      tft.setTextColor(ST7796S_BLACK);
      tft.setCursor(100, 80);
      tft.print(lastVoltage, 3);

      tft.setTextColor(ST7796S_WHITE);
      tft.setCursor(100, 80);
      tft.print(voltage, 3);
      tft.setCursor(310, 80);
      tft.print(" V");
      lastVoltage = voltage;
    }

    // Current (partial fill only if changed)
    if (current != lastCurrent)
    {
      tft.setTextColor(ST7796S_BLACK);
      tft.setCursor(100, 150);
      tft.print(lastCurrent, 3);

      tft.setTextColor(ST7796S_WHITE);
      tft.setCursor(100, 150);
      tft.print(current, 3);
      tft.setCursor(310, 150);
      tft.print(" A");
      lastCurrent = current;
    }

    // Power (partial fill only if changed)
    power = current * voltage;
    if (lastPower != power) {
      tft.setTextSize(1);

      tft.setTextColor(ST7796S_BLACK);
      tft.setCursor(100, 220);
      tft.print(lastPower, 2);

      tft.setTextColor(ST7796S_PURPLE);
      tft.setCursor(100, 220);
      tft.print(power, 2);
      tft.setCursor(310, 220);
      tft.print(" W");
      lastPower = power;
    }
    // Indicators (CC/CV and others) - partial update if status changed
    if (isCV != lastIsCV || loadOn != lastLoadOn || protectOVP != lastProtectOVP || protectOCP != lastProtectOCP || protectOTP != lastProtectOTP)
    {
      setSmallFont();

      tft.setTextColor(isCV ? ST7796S_GREEN : ST7796S_RED);
      tft.setCursor(60, 300);
      tft.print("CV  ");
      tft.setTextColor(!isCV ? ST7796S_GREEN : ST7796S_RED);
      tft.print("CC  ");
      tft.setTextColor(protectOVP ? ST7796S_RED : ST7796S_GREEN);
      tft.print("OVP  ");
      tft.setTextColor(protectOCP ? ST7796S_RED : ST7796S_GREEN);
      tft.print("OCP  ");
      tft.setTextColor(protectOTP ? ST7796S_RED : ST7796S_GREEN);
      tft.print("OTP  ");
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