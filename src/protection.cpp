#include "protection.hpp"
#include "adc.hpp" // Include adc.hpp to use adc::readTemperature

namespace protection {
  bool checkOV(float voltage) {
    return voltage > 20.0; // Example: 20V threshold
  }

  bool checkOC(float current) {
    return current > 2.0; // Example: 2A threshold
  }

  bool checkTemp() {
    float temp = adc::readTemperature(); // Correct function call
    return temp > 70.0; // Example: 70°C threshold
  }
}