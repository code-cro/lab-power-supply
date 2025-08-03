#ifndef PINS_HPP
#define PINS_HPP

// --- Rotary Encoder Pins ---
#define ENC_CLK PB6
#define ENC_DT  PB7
#define ENC_SW  PB8  // Encoder push button

// --- TFT Display Pins (SPI1) ---
#define TFT_CS   PA4  // Chip Select
#define TFT_DC   PA2  // Data/Command
#define TFT_RST  PA1  // Reset
#define TFT_SCK  PA5  // Serial Clock (SPI1 SCK)
#define TFT_MOSI PA7  // Master Out Slave In (SPI1 MOSI)

// --- Push Buttons ---
#define BTN_SET  PB5  // Button 1: Set voltage/current
#define BTN_FINE PB4  // Button 2: Fine/Coarse toggle
#define BTN_OUT  PB3  // Button 3: Output toggle

#endif
