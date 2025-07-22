#ifndef PROTECTION_HPP
#define PROTECTION_HPP

namespace protection {
  bool checkOV(float voltage);
  bool checkOC(float current);
  bool checkTemp();
}

#endif