#ifndef UI_HPP
#define UI_HPP

#include <Adafruit_ST7796S_kbv.h>

namespace ui {
  void drawPage(int page, float voltage, float current, bool isCV, bool loadOn, bool protectOVP, bool protectOCP, bool protectOTP);
  void drawMainView(float voltage, float current, bool isCV, bool loadOn, bool protectOVP, bool protectOCP, bool protectOTP);
}

#endif