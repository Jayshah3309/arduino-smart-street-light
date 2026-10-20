# Setup and calibration

## Upload

Use Arduino IDE 2.x with the Arduino AVR Boards core and Arduino Uno selected. Open the `.ino` inside its matching folder, leaving `control.h` in the same folder. Select your actual serial port and upload. A charge-only USB cable will not provide a serial connection. Close competing serial applications if the port is busy.

For reproducibility, record IDE version, AVR core version, board, port and firmware commit in your test report. CLI commands are in the README.

## Check sensors first

Open Serial Monitor at 115200 baud. CSV columns are:

`ms,ldr_raw,ldr_avg,night,ir1,ir2,ir3,pwm1,pwm2,pwm3`

IR columns show logical detection (1 = detected), not the electrical pin level. Cover and illuminate the LDR: this divider must produce a LOWER reading in darkness. If the response is reversed, fix the divider to match the wiring guide before calibrating.

Move an object in front of each IR sensor; only its matching IR column should become 1. Adjust the module potentiometer. If detection is inverted, confirm the module output polarity and change `IR_ACTIVE_LEVEL` in the sketch. Verify voltage compatibility. INPUT_PULLUP makes a disconnected input inactive for active-LOW modules, but this is not a sensor-fault diagnostic.

## Choose thresholds

1. Record stable `ldr_avg` readings under the intended bright and dark conditions.
2. Select `ENTER_NIGHT` and `ENTER_DAY` between the two groups, keeping `ENTER_NIGHT < ENTER_DAY`. Defaults 350 and 450 are examples only.
3. Test transitions slowly in both directions. Between thresholds the existing state must persist.
4. If the board boots within this band, it defaults to day until the night threshold is crossed. Record whether this is suitable for your application.
5. Re-upload after edits and record the final values. LDR counts are not lux measurements.

Eight samples at a 20 ms interval form the moving average. This introduces response smoothing; actual reaction time must be measured. Change DIM_PWM, BRIGHT_PWM and HOLD_MS only within valid types/ranges and repeat the relevant tests. All LED pins must remain PWM-capable UNO pins.

## Troubleshooting

| Symptom | Check |
|---|---|
| LEDs never light | Darkness threshold, polarity, common GND, series resistors |
| LEDs always bright at night | IR polarity, sensitivity, nearby reflective surfaces |
| Lights oscillate | LDR placement, threshold separation, power and sensor noise |
| One zone affects another | Compare D2→D3, D4→D5, D7→D6 against wiring |
| Upload fails | UNO selection, serial port, cable, port held by another program |
| Strange serial text | Set monitor to 115200 baud |
