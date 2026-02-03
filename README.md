# Ultrasonic HC-SR04 with Arduino Uno R4 WiFi

A small PlatformIO project that reads distance measurements from an HC‑SR04 ultrasonic sensor and prints them over serial using an Arduino Uno R4 WiFi.

## Project summary

The example code in `src/main.cpp` triggers the HC‑SR04 sensor, measures the echo pulse width with `pulseIn()`, converts the time to distance (cm), and prints the result via Serial at 9600 baud.

## Hardware

- Arduino Uno R4 WiFi (board used in `platformio.ini`)
- HC‑SR04 ultrasonic distance sensor
- Breadboard and jumper wires
- Optional: logic level shifter (if your target board's I/O is not 5V tolerant)

Tested board: `uno_r4_wifi` (see `platformio.ini`).

## Wiring

Connect the HC‑SR04 pins to the Arduino as follows (pins are taken from `src/main.cpp`):

- HC‑SR04 VCC -> 5V (Arduino 5V)
- HC‑SR04 GND -> GND
- HC‑SR04 TRIG -> D9 (defined as `trigPin` in `src/main.cpp`)
- HC‑SR04 ECHO -> D10 (defined as `echoPin` in `src/main.cpp`)

Note: The HC‑SR04 Echo pin outputs 5V. Many Arduino boards accept 5V signals on their digital inputs, but if you're unsure about the Uno R4 WiFi's I/O voltage tolerance or you're interfacing with a 3.3V microcontroller, use a simple voltage divider or a level shifter on the Echo line.

## Files of interest

- `src/main.cpp` — sensor read logic and serial output
- `platformio.ini` — build environment (env: `uno_r4_wifi`, platform `renesas-ra`, framework `arduino`)

Key snippets from the code:

- Trigger pulse: 10 µs HIGH (after a 2 µs LOW)
- Measurement: `long duration = pulseIn(echoPin, HIGH);`
- Distance calculation: `distance = duration * 0.034 / 2;` (speed of sound ≈ 0.034 cm/µs)
- Serial baud rate: `Serial.begin(9600);`

## Build, upload and monitor (PlatformIO)

Open a terminal in the project root and run:

```powershell
# Build the project for the uno_r4_wifi environment
pio run -e uno_r4_wifi

# Upload the compiled firmware to the board
pio run -e uno_r4_wifi -t upload

# Open the serial monitor (uses the environment's default args) at 9600 baud
pio device monitor -e uno_r4_wifi --baud 9600
```

If PlatformIO can't auto-detect the serial port, list ports with `pio device list` and pass the port explicitly:

```powershell
pio device monitor -p COM3 --baud 9600
```

## How it works (brief)

1. `trigPin` is set LOW for 2 µs, then HIGH for 10 µs to send an ultrasonic burst.
2. `pulseIn(echoPin, HIGH)` waits for the returning echo pulse and returns its duration in microseconds.
3. Distance in centimeters is calculated as: distance = (duration * 0.034) / 2.
4. The distance is printed to Serial as `Distance: <value> cm` every loop iteration (loop has `delay(100)`).

You can change the trigger/echo pins by editing the `#define trigPin` and `#define echoPin` lines in `src/main.cpp`.

## Usage and tips

- Open the serial monitor at 9600 baud to see distance readings.
- For stable readings, make sure the sensor has a clear path to the target — avoid angled or soft surfaces.
- Add averaging or median filtering in the code if readings are noisy.
- If distance reads `0` or a very high value, check wiring and that the Echo pin is actually receiving the signal.
- If you get no serial output, verify the board is powered and the correct port/env is used.

## Troubleshooting checklist

- Wiring: confirm VCC and GND are connected, TRIG -> D9, ECHO -> D10.
- Power: HC‑SR04 needs 5V; insufficient power causes unstable readings.
- Baud rate: ensure serial monitor is set to 9600.
- Pin definitions: if you changed pins, rebuild and reupload.
- Level shifting: if using a 3.3V MCU, use a level shifter on ECHO.
- Pulse timing: ensure the trigger pulse is 10 µs as in the code.

## Customization

- Change sampling rate by modifying the `delay(100)` in `loop()`.
- Smooth readings by taking multiple `pulseIn()` samples and averaging.

## License

This project is provided under the MIT License — see below.

MIT License

Copyright (c) YEAR Your Name

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

[Full MIT license text omitted for brevity — replace YEAR and Your Name above.]

---

If you'd like, I can also:
- Add an ASCII wiring diagram or a simple SVG breadboard diagram.
- Replace the placeholder license text with the full MIT license and your name/year.
- Add a small note or code snippet that implements averaging of multiple measurements.
