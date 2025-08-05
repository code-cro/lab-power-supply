#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7796S_kbv.h>

// --- Pin Configuration ---
#define ENC_CLK PB6
#define ENC_DT  PB7
#define ENC_SW  PB8

#define BTN_SET  PB3
#define BTN_FINE PB4
#define BTN_OUT  PB5

#define TFT_CS   PA4
#define TFT_DC   PA2
#define TFT_RST  PA1
#define TFT_SCK  PA5
#define TFT_MOSI PA7

// --- Display ---
Adafruit_ST7796S_kbv tft = Adafruit_ST7796S_kbv(TFT_CS, TFT_DC, TFT_RST);

// --- Rotary Encoder State ---
volatile int16_t encoderPosition = 0;
int16_t lastEncoderPosition = 0;
int8_t lastEncoded = 0;

// --- Encoder ISR ---
void encoderISR() {
  int MSB = digitalRead(ENC_CLK);
  int LSB = digitalRead(ENC_DT);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderPosition++;
  else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderPosition--;

  lastEncoded = encoded;
}

// --- Encoder Button ---
bool encoderPressed = false;
void encoderButtonISR() {
  encoderPressed = true;
}

// --- Button States ---
bool buttonStates[3] = {false, false, false};
bool lastButtonStates[3] = {false, false, false};
const uint8_t buttons[] = {BTN_SET, BTN_FINE, BTN_OUT};

// --- Debounce ---
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTimes[3] = {0, 0, 0};

// --- UI Helpers ---
void drawLabel(const char* label, int x, int y) {
  tft.setTextColor(ST7796S_WHITE);
  tft.setCursor(x, y);
  tft.print(label);
}

void drawValue(const char* label, int x, int y, bool current, bool& last) {
  if (current != last) {
    tft.setTextColor(ST7796S_BLACK);
    tft.setCursor(x, y);
    tft.print(last ? "YES" : "NO ");

    tft.setTextColor(ST7796S_WHITE);
    tft.setCursor(x, y);
    tft.print(current ? "YES" : "NO ");
    last = current;
  }
}

void setup() {

  // Init display
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ST7796S_BLACK);
  tft.setTextSize(2);

  // Labels
  drawLabel("Encoder:", 20, 40);
  drawLabel("Pressed:", 20, 80);
  drawLabel("Btn1 SET:", 20, 120);
  drawLabel("Btn2 FINE:", 20, 160);
  drawLabel("Btn3 OUT:", 20, 200);

  // Pins
  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_FINE, INPUT_PULLUP);
  pinMode(BTN_OUT, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENC_CLK), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_DT), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_SW), encoderButtonISR, FALLING);
}

void loop() {
  static int16_t displayedEncoder = 0;
  if (encoderPosition != displayedEncoder) {
    tft.setTextColor(ST7796S_BLACK);
    tft.setCursor(160, 40);
    tft.print(displayedEncoder);

    tft.setTextColor(ST7796S_WHITE);
    tft.setCursor(160, 40);
    tft.print(encoderPosition);
    displayedEncoder = encoderPosition;
  }

  static bool lastEncoderPressed = false;
  if (encoderPressed != lastEncoderPressed) {
    tft.setTextColor(ST7796S_BLACK);
    tft.setCursor(160, 80);
    tft.print(lastEncoderPressed ? "YES" : "NO ");

    tft.setTextColor(ST7796S_WHITE);
    tft.setCursor(160, 80);
    tft.print(encoderPressed ? "YES" : "NO ");

    lastEncoderPressed = encoderPressed;
    encoderPressed = false;  // reset after display
  }

  for (int i = 0; i < 3; i++) {
    bool reading = digitalRead(buttons[i]) == LOW;
    if (reading != lastButtonStates[i]) {
      lastDebounceTimes[i] = millis();
    }
    if ((millis() - lastDebounceTimes[i]) > debounceDelay) {
      if (reading != buttonStates[i]) {
        buttonStates[i] = reading;
      }
    }
    drawValue("", 160, 120 + (i * 40), buttonStates[i], lastButtonStates[i]);
  }

  delay(20);
}
