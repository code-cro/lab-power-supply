#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S_kbv.h>
#include <RobotoMono_Regular12pt7b.h>
#include <RobotoMono_Regular24pt7b.h>
#include "pins.hpp"
#include "ui.hpp"

extern Adafruit_ST7796S_kbv tft;

namespace ui {
  void drawPage(int page, float voltage, float current, bool isCV, bool loadOn, bool protectOVP, bool protectOCP, bool protectOTP, int encoderPos, bool encBtnShort, bool encBtnLong, bool btnSet, bool btnFine, bool btnOut) {
    static int currentPage = -1;
    if (page != currentPage) {
      tft.fillScreen(ST7796S_BLACK); // Clear screen on page change
      currentPage = page;
    }

    if (page == 0) {
      drawMainView(voltage, current, isCV, loadOn, protectOVP, protectOCP, protectOTP);
    } else if (page == 1) {
      drawInputTestPage(encoderPos, encBtnShort, encBtnLong, btnSet, btnFine, btnOut);
    }
  }

  void drawMainView(float voltage, float current, bool isCV, bool loadOn, bool protectOVP, bool protectOCP, bool protectOTP) {
    static float lastVoltage = -1.0;
    static float lastCurrent = -1.0;
    static bool lastIsCV = false;
    static bool lastLoadOn = false;
    static bool lastProtectOVP = false;
    static bool lastProtectOCP = false;
    static bool lastProtectOTP = false;

    tft.setFont(&RobotoMono_Regular24pt7b);
    tft.setTextSize(1);

    if (voltage != lastVoltage) {
      tft.fillRect(120, 28, 200, 56, ST7796S_BLACK);
      tft.setTextColor(ST7796S_WHITE);
      tft.setCursor(120, 80);
      tft.print(voltage, 3);
      tft.setCursor(310, 80);
      tft.print(" V");
      lastVoltage = voltage;
    }

    if (current != lastCurrent) {
      tft.fillRect(120, 100, 200, 56, ST7796S_BLACK);
      tft.setTextColor(ST7796S_WHITE);
      tft.setCursor(120, 150);
      tft.print(current, 3);
      tft.setCursor(310, 150);
      tft.print(" A");
      lastCurrent = current;
    }

    tft.fillRect(120, 190, 200, 38, ST7796S_BLACK);
    tft.setTextColor(ST7796S_ORANGE);
    tft.setCursor(120, 220);
    tft.print(voltage * current, 3);
    tft.setCursor(310, 220);
    tft.print(" W");

    if (isCV != lastIsCV || loadOn != lastLoadOn || protectOVP != lastProtectOVP || protectOCP != lastProtectOCP || protectOTP != lastProtectOTP) {
      tft.setFont(&RobotoMono_Regular12pt7b);
      tft.setTextSize(1);
      tft.fillRect(60, 300 - 72, 480, 72, ST7796S_BLACK);
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

  void drawInputTestPage(int encoderPos, bool encBtnShort, bool encBtnLong, bool btnSet, bool btnFine, bool btnOut) {
    tft.setFont(&RobotoMono_Regular24pt7b);
    tft.setTextSize(1);
    tft.setTextColor(ST7796S_WHITE);

    // Title
    tft.setCursor(20, 30);
    tft.print("Input Test Page");

    // Encoder Position
    tft.fillRect(20, 50, 440, 56, ST7796S_BLACK);
    tft.setCursor(20, 80);
    tft.printf("Encoder Pos: %d", encoderPos);

    // Encoder Button
    tft.fillRect(20, 100, 440, 56, ST7796S_BLACK);
    tft.setCursor(20, 130);
    tft.setTextColor(encBtnShort ? ST7796S_GREEN : ST7796S_RED);
    tft.print("Enc Short: ");
    tft.print(encBtnShort ? "Pressed" : "Released");
    tft.setCursor(250, 130);
    tft.setTextColor(encBtnLong ? ST7796S_GREEN : ST7796S_RED);
    tft.print("Enc Long: ");
    tft.print(encBtnLong ? "Pressed" : "Released");

    // Buttons
    tft.fillRect(20, 150, 440, 56, ST7796S_BLACK);
    tft.setCursor(20, 180);
    tft.setTextColor(btnSet ? ST7796S_GREEN : ST7796S_RED);
    tft.print("SET: ");
    tft.print(btnSet ? "Pressed" : "Released");
    tft.setCursor(160, 180);
    tft.setTextColor(btnFine ? ST7796S_GREEN : ST7796S_RED);
    tft.print("FINE: ");
    tft.print(btnFine ? "Pressed" : "Released");
    tft.setCursor(300, 180);
    tft.setTextColor(btnOut ? ST7796S_GREEN : ST7796S_RED);
    tft.print("OUT: ");
    tft.print(btnOut ? "Pressed" : "Released");
  }
}