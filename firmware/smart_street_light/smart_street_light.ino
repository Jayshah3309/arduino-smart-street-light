/* Smart Street Light - proposed three-zone Arduino UNO R3 reference design.
 * Hardware verification pending. See hardware/wiring.md before connecting.
 * No external libraries. Serial monitor: 115200 baud.
 */
#include "control.h"

constexpr uint8_t LDR_PIN = A0;
constexpr uint8_t IR_PINS[] = {2, 4, 7};
constexpr uint8_t LED_PINS[] = {3, 5, 6}; // UNO R3 PWM outputs
constexpr uint8_t ZONES = sizeof(IR_PINS) / sizeof(IR_PINS[0]);
constexpr uint8_t IR_ACTIVE_LEVEL = LOW; // Confirm against your module
constexpr uint16_t ENTER_NIGHT = 350; // Example values; calibrate locally
constexpr uint16_t ENTER_DAY = 450;
constexpr uint8_t DIM_PWM = 40;
constexpr uint8_t BRIGHT_PWM = 255;
constexpr uint32_t SAMPLE_MS = 20;
constexpr uint32_t HOLD_MS = 3000;
constexpr uint32_t LOG_MS = 500;
constexpr uint8_t FILTER_SAMPLES = 8;
static_assert(ENTER_NIGHT < ENTER_DAY, "Night threshold must be lower");
static_assert(DIM_PWM < BRIGHT_PWM, "Dim must be below bright");

uint16_t readings[FILTER_SAMPLES];
uint32_t total = 0;
uint8_t sampleIndex = 0;
uint16_t filteredLight = 0;
bool night = false;
bool seen[ZONES] = {};
uint32_t lastSeen[ZONES] = {};
uint8_t outputs[ZONES] = {};
uint32_t lastSample = 0;
uint32_t lastLog = 0;

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < ZONES; ++i) {
    pinMode(IR_PINS[i], INPUT_PULLUP);
    pinMode(LED_PINS[i], OUTPUT);
    analogWrite(LED_PINS[i], 0);
  }
  filteredLight = analogRead(LDR_PIN);
  for (uint8_t i = 0; i < FILTER_SAMPLES; ++i) {
    readings[i] = filteredLight;
    total += filteredLight;
  }
  Serial.println(F("Reference firmware; calibrate LDR and IR before use."));
  Serial.println(F("ms,ldr_raw,ldr_avg,night,ir1,ir2,ir3,pwm1,pwm2,pwm3"));
}

void loop() {
  const uint32_t now = millis();
  static uint16_t rawLight = 0;
  if (uint32_t(now - lastSample) >= SAMPLE_MS) {
    lastSample = now;
    rawLight = analogRead(LDR_PIN);
    total -= readings[sampleIndex];
    readings[sampleIndex] = rawLight;
    total += rawLight;
    sampleIndex = (sampleIndex + 1) % FILTER_SAMPLES;
    filteredLight = total / FILTER_SAMPLES;
    night = streetlight::updateNight(night, filteredLight, ENTER_NIGHT, ENTER_DAY);
  }
  for (uint8_t i = 0; i < ZONES; ++i) {
    const bool detected = digitalRead(IR_PINS[i]) == IR_ACTIVE_LEVEL;
    if (night && detected) {
      seen[i] = true;
      lastSeen[i] = now;
    }
    if (!night) seen[i] = false;
    const bool active = streetlight::holdActive(seen[i], now, lastSeen[i], HOLD_MS);
    outputs[i] = streetlight::brightness(night, active, DIM_PWM, BRIGHT_PWM);
    analogWrite(LED_PINS[i], outputs[i]);
  }
  if (uint32_t(now - lastLog) >= LOG_MS) {
    lastLog = now;
    Serial.print(now); Serial.print(',');
    Serial.print(rawLight); Serial.print(',');
    Serial.print(filteredLight); Serial.print(','); Serial.print(night);
    for (uint8_t i = 0; i < ZONES; ++i) {
      Serial.print(','); Serial.print(digitalRead(IR_PINS[i]) == IR_ACTIVE_LEVEL);
    }
    for (uint8_t i = 0; i < ZONES; ++i) {
      Serial.print(','); Serial.print(outputs[i]);
    }
    Serial.println();
  }
}
