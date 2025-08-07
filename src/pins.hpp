#ifndef PINS_HPP
#define PINS_HPP

// Rotary Encoder Pins
#define ENC_CLK PB6
#define ENC_DT  PB7
#define ENC_SW  PB8

// TFT Display Pins (SPI1)
#define TFT_CS   PA4
#define TFT_DC   PA2
#define TFT_RST  PA1
#define TFT_SCK  PA5
#define TFT_MOSI PA7

// Push Buttons
#define BTN_SET  PB5
#define BTN_FINE PB4
#define BTN_OUT  PB3

// I2C Pins (for touch controller, adjust if different)
#define I2C_SDA PB9
#define I2C_SCL PB8

#endif