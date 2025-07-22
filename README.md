# 🔧 STM32F411 UI Interface – Lab Power Supply

## 🧩 Hardware Components

| Component                    | Description                                                   |
|-----------------------------|---------------------------------------------------------------|
| **STM32F411CEU6**           | Black Pill board, 3.3V logic, 100+ MHz ARM Cortex-M4          |
| **3.5" TFT LCD (ST7796)**    | SPI interface, 480×320 resolution                             |
| **Rotary Encoder (EC11)**   | With push button (optional) for UI control                   |
| **2× 10kΩ Resistors**       | Optional pull-ups for encoder if not using `INPUT_PULLUP`     |
| **Dupont Wires**            | For wiring connections                                        |
| **Breadboard or Custom PCB**| Optional – for clean layout                                   |
| **USB to Serial / ST-Link** | For flashing STM32 firmware                                   |

---

## 📡 Pin Mapping

### TFT ST7796 SPI Display → STM32F411

| Display Pin | STM32 Pin | Description      |
|-------------|-----------|------------------|
| `CS`        | `PA4`     | Chip Select      |
| `DC`        | `PA3`     | Data/Command     |
| `RST`       | `PA2`     | Hardware Reset   |
| `SCK`       | `PA5`     | SPI1 Clock       |
| `MOSI`      | `PA7`     | SPI1 Data Out    |
| `VCC`       | 3.3V/5V   | Match display spec |
| `GND`       | GND       | Ground           |

### Rotary Encoder → STM32F411

| Encoder Pin | STM32 Pin | Notes              |
|-------------|-----------|--------------------|
| `CLK`       | `PB6`     | Use interrupt pin  |
| `DT`        | `PB7`     | Direction detect   |
| `SW`        | (Optional)| Button input       |
| `VCC`       | 3.3V/5V   | Power              |
| `GND`       | GND       | Ground             |

---

## 🔌 Power Notes

- **TFT VCC**: Check whether your display uses 3.3V or supports 5V input. Most ST7796 modules include an onboard regulator and level shifter.
- **STM32F411**: Runs at 3.3V logic. Don’t feed 5V signals directly to input pins.

---

## 🔄 Rotary Encoder Behavior

| Action               | Effect                     |
|----------------------|----------------------------|
| Rotate Clockwise     | Go to next UI page         |
| Rotate Counterclockwise | Go to previous page     |
| Button Press (optional) | Trigger function (future)|

---

## 📺 UI Pages

| Page         | Description                         |
|--------------|-------------------------------------|
| `Main View`  | Shows voltage, current, power, mode |
| `Graph View` | Placeholder for future graphing     |
| `Preset View`| Placeholder for preset selection    |

---

## 🛠 Libraries Required

Install these in your PlatformIO or Arduino-style environment:

- `Adafruit_GFX`
- `Adafruit_ST7796S_kbv` *(custom fork for ST7796, works well with STM32)*

---

## 🧪 Future Ideas

- Touch support (if display supports)
- Real-time V/I from ADC
- EEPROM preset save/load
- UI-controlled load switch
- Logging to SD card

---
