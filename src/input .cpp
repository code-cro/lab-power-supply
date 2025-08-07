#include "Arduino.h"
#include "input.hpp"
#include "pins.hpp"

namespace input {
  static volatile Action lastAction = Action::None;
  static bool lastEncA = HIGH;
  static unsigned long encBtnDownTime = 0;
  static bool encBtnWasDown = false;

  void init() {
    pinMode(ENC_CLK, INPUT_PULLUP);
    pinMode(ENC_DT, INPUT_PULLUP);
    pinMode(ENC_SW, INPUT_PULLUP);
    pinMode(BTN_SET, INPUT_PULLUP);
    pinMode(BTN_FINE, INPUT_PULLUP);
    pinMode(BTN_OUT, INPUT_PULLUP);
  }

  void poll() {
    // Rotary encoder
    static bool prevA = digitalRead(ENC_CLK);
    bool currA = digitalRead(ENC_CLK);
    bool currB = digitalRead(ENC_DT);

    if (currA != prevA) {
      if (currA == LOW) { // Trigger on falling edge
        lastAction = currB ? Action::RotateCCW : Action::RotateCW;
      }
    }
    prevA = currA;

    // Encoder Button
    bool swState = digitalRead(ENC_SW) == LOW;
    unsigned long now = millis();
    if (swState && !encBtnWasDown) {
      encBtnDownTime = now;
      encBtnWasDown = true;
    } else if (!swState && encBtnWasDown) {
      if (now - encBtnDownTime > 1000) {
        lastAction = Action::LongPress;
      } else if (now - encBtnDownTime > 20) {
        lastAction = Action::Press;
      }
      encBtnWasDown = false;
    }

    // Buttons
    static unsigned long lastBtnTime[3] = {0, 0, 0};
    static bool lastBtnState[3] = {HIGH, HIGH, HIGH};
    int btnPins[3] = {BTN_SET, BTN_FINE, BTN_OUT};
    Action btnActions[3] = {Action::Btn1, Action::Btn2, Action::Btn3};

    for (int i = 0; i < 3; i++) {
      bool currState = digitalRead(btnPins[i]) == LOW;
      if (currState != lastBtnState[i]) {
        lastBtnTime[i] = now;
      }
      if (currState && (now - lastBtnTime[i]) > 20) { // 20ms debounce
        lastAction = btnActions[i];
      }
      lastBtnState[i] = currState;
    }
  }

  Action getAction() {
    Action a = lastAction;
    lastAction = Action::None;
    return a;
  }
}