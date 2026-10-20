# Limitations and roadmap

## Present limits

This is a three-zone, low-voltage indicator-LED reference design. No network connectivity, outdoor enclosure, certified luminaire driver, battery, solar charger, fault detection or calibrated illuminance sensor is included. IR reflection does not prove a person or vehicle is present. Disconnected or stuck sensors are not reliably diagnosed. Controller failure behaviour and real-world lighting requirements have not been evaluated.

## Next work, in order

1. Compare all pins and parts with the original model; adapt firmware and drawing together.
2. Calibrate LDR thresholds and IR polarity using serial logs.
3. Complete hardware acceptance tests and attach actual photo/video evidence.
4. Measure baseline and automatic energy for a specified scenario.
5. Investigate hold time, threshold robustness and outdoor sensor limitations.
6. If required later: engineer a power driver, evaluate alternative presence sensors, or add network monitoring. Treat each as a separate tested extension.

Solar power requires an independently specified charging and battery design. Remote monitoring would require networking hardware and firmware. Neither is a current feature.
