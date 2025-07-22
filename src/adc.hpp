#ifndef ADC_HPP
#define ADC_HPP

namespace adc {
  void init();
  float readVoltage();
  float readCurrent();
  float readTemperature();
}

#endif