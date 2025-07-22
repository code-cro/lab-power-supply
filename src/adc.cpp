#include <Adafruit_ADS1X15.h>

extern Adafruit_ADS1115 ads;

namespace adc {
  void init() {
    ads.setGain(GAIN_ONE); // ±4.096V range
    ads.begin();
  }

  float readVoltage() {
    int16_t adc0 = ads.readADC_SingleEnded(0); // AIN0
    float volts = (adc0 * 4.096) / 32767.0; // Convert to volts (adjust scaling as needed)
    return volts;
  }

  float readCurrent() {
    int16_t adc1 = ads.readADC_SingleEnded(1); // AIN1 (shunt resistor)
    float volts = (adc1 * 4.096) / 32767.0;
    float current = volts / 0.1; // Example: 0.1Ω shunt resistor
    return current;
  }

  float readTemperature() {
    int16_t adc2 = ads.readADC_SingleEnded(2); // AIN2 (NTC thermistor)
    float volts = (adc2 * 4.096) / 32767.0;
    // Example: NTC thermistor calculation (adjust for your thermistor)
    float resistance = (volts * 10000) / (3.3 - volts); // 10kΩ pull-up
    float temp = 1.0 / (1.0 / 298.15 + log(resistance / 10000.0) / 3950.0) - 273.15; // Steinhart-Hart
    return temp;
  }
}