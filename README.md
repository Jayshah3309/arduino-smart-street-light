# Smart Street Light System Using Arduino

An Arduino UNO R3 reference design for automatic day/night lighting and independent object-triggered brightness control across three LED zones.

**Status:** new reference implementation. The original repository contained no firmware or hardware files. These pin assignments, component quantities and settings are proposed, not a reconstruction of the original physical project. Hardware testing, photographs, video and power measurements are pending. This is a small LED demonstration model, not a street-lamp driver or a network-connected IoT system.

![Proposed reference wiring](hardware/circuit.svg)

## Problem statement
Fixed-brightness lighting can remain on when daylight or a lack of nearby activity makes full output unnecessary. This prototype demonstrates ambient-light gating and local brightness control using an LDR and IR sensors. Any energy benefit must be established by measurement.

## Reference behaviour

| Ambient condition | Zone sensor | Output for that zone |
|---|---|---|
| Daylight | Either state | OFF |
| Darkness | No detection or expired hold | DIM: PWM 40/255 |
| Darkness | Object detected | BRIGHT: PWM 255/255 |
| Darkness | Object leaves | BRIGHT for 3 seconds after last detection, then DIM |

Each sensor controls its corresponding LED. All outputs turn off in daylight. Between the two LDR thresholds, the previous day/night state is retained; at startup this band defaults to day. An eight-sample moving average reduces LDR fluctuations. Timing uses `millis()` without blocking delays.

## Contents

- [Firmware](firmware/smart_street_light/smart_street_light.ino) and shared control logic
- [Components, wiring and power](hardware/wiring.md)
- [Setup and calibration](docs/setup.md)
- [Test procedure and evidence status](docs/testing.md)
- [Measurement worksheet](docs/measurements.csv)
- [Limitations and roadmap](docs/roadmap.md)
- [Contributors and evidence](docs/contributors.md)

## Components (proposed reference build)

| Component | Quantity | Notes |
|---|---:|---|
| Arduino UNO R3 | 1 | ATmega328P, 5 V logic |
| LDR | 1 | With 10 kΩ divider resistor |
| Digital IR obstacle module | 3 | 5 V-compatible; verify active level |
| Small indicator LED | 3 | Select low-current parts |
| 1 kΩ LED resistor | 3 | One series resistor per LED |
| 10 kΩ resistor | 1 | LDR divider |
| Breadboard, jumpers, USB cable | As needed | Common ground |

## Quick start

1. Read [wiring](hardware/wiring.md); do not connect an existing model without checking pin compatibility.
2. Download or clone this repository. Open `firmware/smart_street_light/smart_street_light.ino` in Arduino IDE. Keep `control.h` beside it.
3. Install/select **Arduino AVR Boards → Arduino Uno**, choose the correct port and upload. No third-party library is required.
4. Open Serial Monitor at **115200 baud** and perform [calibration](docs/setup.md).
5. Execute the [hardware test checklist](docs/testing.md) before describing the prototype as validated.

Optional Arduino CLI build:

```sh
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli compile --fqbn arduino:avr:uno firmware/smart_street_light
```

## Validation

Host-side tests check hysteresis boundaries, independent brightness decisions, hold expiry and 32-bit clock wraparound. Run:

```sh
g++ -std=c++11 -Wall -Wextra -Werror tests/control_test.cpp -o /tmp/streetlight-test
/tmp/streetlight-test
```

GitHub Actions also builds for UNO and runs the host tests. Software checks do not validate physical wiring, sensor detection, illumination or energy savings. See [testing status](docs/testing.md).

## Evidence and contributors

Actual prototype photographs, demonstration video, hardware results and team roles have not been supplied. Instructions for adding them are in [media/README.md](media/README.md) and [contributors](docs/contributors.md). No generated illustration is presented as a real prototype photograph.

## Limitations and future scope

IR obstacle modules detect reflected objects, not specifically people or vehicle identity. Outdoor sunlight, reflectivity and mounting affect performance. LDR readings are relative ADC counts, not calibrated lux. See the [roadmap](docs/roadmap.md) for proposed extensions; remote monitoring, solar power and fault detection are not implemented.

## License and references

No reuse license has been selected by the owner yet. See [LICENSE](LICENSE). Adapted or third-party contributions must retain their original notices.

- [Arduino UNO R3](https://docs.arduino.cc/hardware/uno-rev3/)
- [Arduino PWM guide](https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino)
- [Arduino analog smoothing example](https://docs.arduino.cc/built-in-examples/analog/Smoothing/)
- [GitHub README guidance](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/about-readmes)
