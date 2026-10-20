# Validation and evidence

## Current status

- New reference firmware and documentation: added.
- Host control-logic tests: run locally; see commit delivery notes / Actions for results.
- Full UNO target compile: use GitHub Actions or Arduino CLI; a host syntax check is not a substitute.
- Physical circuit, sensors, detection range, delay, power: **not tested**.
- Original project compatibility: **not verified**.
- Real prototype photo, demonstration video and simulator: **not supplied**.

## Hardware acceptance checklist

Record date, tester, board, component models, supply voltage, firmware commit, toolchain version and final constants. Complete the observed result and pass/fail columns only after execution.

| ID | Procedure | Expected | Observed / result |
|---|---|---|---|
| H1 | Illuminate LDR; trigger all IR sensors | All LEDs OFF | Not run |
| H2 | Cover LDR; leave sensors clear | All LEDs DIM | Not run |
| H3 | At night trigger IR1, then IR2, then IR3 separately | Only matching zone BRIGHT | Not run |
| H4 | Remove object at night | Matching zone dims about 3 s after last detection | Not run |
| H5 | Retrigger during hold | Hold extends from most recent detection | Not run |
| H6 | Detect on two or three zones | Each detected zone brightens independently | Not run |
| H7 | Illuminate LDR while a zone is bright | All LEDs OFF after filtered threshold crossing | Not run |
| H8 | Vary LDR within threshold band | Previous day/night state retained | Not run |
| H9 | Restart in daylight, dark and threshold band | Off / night behaviour / default day respectively | Not run |
| H10 | Run repeatedly for 30 minutes | No unexpected reset or unstable operation | Not run |
| H11 | Test sunlight, dark/reflective objects and different distances | Record misses and false triggers; do not assume outdoor suitability | Not run |

## Host tests

`tests/control_test.cpp` exercises actual shared control functions, including both hysteresis boundaries, no-detection startup, hold expiry, clock rollover, and independent output decisions. These tests do not emulate ADC electronics, IR modules, serial timing or the AVR runtime.

## Power measurement procedure

Compare a baseline with all three LEDs continuously at PWM 255 against automatic operation using the SAME hardware, regulated voltage, duration and scripted light/object sequence. Include controller and sensor power in both measurements. Use a suitable meter; a meter connected in current mode must be in series, not across the supply.

Record average power with a meter capable of capturing the load behaviour, or integrate measured power over time: E = sum(P_i × Δt_i). Record energy in Wh. Savings (%) = 100 × (E_baseline − E_automatic) / E_baseline, provided baseline energy is positive. Describe uncertainty, instrument, duration and scenario. No measured saving is claimed by this repository. PWM percentage is not system energy saving.

Use [measurements.csv](measurements.csv) as a blank worksheet. Do not replace missing measurements with estimates labelled as results.
