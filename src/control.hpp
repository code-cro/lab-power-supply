#ifndef CONTROL_HPP
#define CONTROL_HPP

namespace control {
  void initPWM();
  void updatePWM(float voltage, float current, bool &isCV, bool &loadOn);
}

#endif