# Wireless EV Charging System

A wireless charging prototype for electric vehicles based on inductive power transfer (IPT). The prototype uses a dual-spot parking setup: a transmitter coil passes power across an air gap to a receiver coil through resonant inductive coupling, and an Arduino handles vehicle detection, switching and monitoring.

This repository contains the Arduino control sketch, the wiring notes and the coil details. As published, the sketch reads one IR sensor and drives one relay, so it controls a single charging spot.

## Publication

I co-authored a paper on this work, published in JETIR (Journal of Emerging Technologies and Innovative Research), Vol. 13, Issue 4, April 2026: [JETIR2604872](https://www.jetir.org/view?paper=JETIR2604872).

## Features

- Vehicle detection with an IR sensor, confirmed for one second before charging starts
- Relay-switched charging that starts when a vehicle arrives and stops when it leaves
- Voltage sensing through a resistor divider and current sensing with an ACS712
- Live voltage, current and power readout on a 16x2 LCD and the Serial Monitor
- Resonant (tuned LC) transmitter and receiver coils
- Safety cut-offs for over-current and low voltage, with LED and buzzer alerts

**Note on efficiency:** the efficiency figure on the LCD comes from `calculateEfficiency()`, which currently returns a simulated placeholder value, not a measurement. Measuring real efficiency needs both input-side and output-side power readings, which this sketch does not take yet.

## Hardware Components

- Arduino Uno or Nano
- Transmitter coil (primary) and receiver coil (secondary)
- IR sensor (vehicle detection)
- 16x2 LCD display
- 5V relay module
- Power MOSFETs
- Capacitors and inductors for the resonant circuit
- ACS712 current sensor
- Voltage divider resistors (10KΩ, 2KΩ)
- 12V DC power supply
- Rectifier diodes
- LED indicators
- Buzzer (optional)

## Software Requirements

- Arduino IDE 1.8+ or 2.x
- LiquidCrystal library (included with the Arduino IDE)

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/Aryanpanwar10005/wireless_ev_charging.git
   ```
2. Open `wireless_ev_charging.ino` in the Arduino IDE.
3. Select your board: Tools → Board → Arduino Uno.
4. Select your port: Tools → Port.
5. Upload to the board.

## Circuit Connections

| Component | Arduino pin |
|---|---|
| IR sensor (active LOW) | D2 |
| Relay module (charging control) | D7 |
| Charging LED | D8 |
| Ready LED | D9 |
| Buzzer | D10 |
| Voltage divider output | A0 |
| ACS712 output | A1 |
| LCD (RS, E, D4, D5, D6, D7) | 12, 11, 5, 4, 3, 6 |

Connect the transmitter coil to the primary circuit with its resonant capacitor, and the receiver coil to the rectifier and load. Full wiring, coil and safety notes are in [circuit.md](circuit.md).

## Usage

1. Power on the system. The LCD shows "System Ready / Waiting...".
2. Place the receiver coil close to the transmitter coil (the sketch notes 2-5 cm as a typical gap).
3. When the IR sensor detects a vehicle, the relay switches the charging circuit on.
4. Voltage, current and power are shown on the LCD and sent to the Serial Monitor (9600 baud).
5. Charging stops when the vehicle is removed, and the LCD shows the session time.

Calibrate the voltage divider ratio and the current sensor constants in the sketch for your hardware before relying on the readings.

## Design Parameters

These are the values used in the sketch and the circuit notes:

- Resonant frequency target: about 85 kHz, set by f = 1 / (2π√(LC))
- Coils: about 20 turns of 18-22 AWG copper wire, 10-15 cm diameter
- Typical coil gap: 2-5 cm
- Supply: 12V DC
- Over-current cut-off: 3 A
- Low-voltage cut-off: 3 V
- Display and serial update interval: 500 ms

## How It Works

- **Transmitter circuit:** high-frequency AC drives the transmitter coil, which produces an alternating magnetic field.
- **Receiver circuit:** the receiver coil picks up the field, and the induced AC is rectified to DC for the load.
- **Resonant tuning:** capacitors tune both coils to the same frequency so that power transfers across the gap.
- **Control:** the Arduino detects the vehicle, switches the relay, reads voltage and current, and shuts down on faults.

## Safety Features

- Over-current cut-off (3 A)
- Low-voltage cut-off
- Emergency stop routine on a fault: relay off, buzzer alert and an LCD message
- Automatic shutdown when the vehicle is removed
- LED and buzzer status alerts

## Future Work

- Measure input and output power to calculate real efficiency
- Higher power output
- Temperature monitoring and thermal management
- Foreign object detection (FOD)
- Battery management system (BMS) integration
- Remote monitoring over Bluetooth or Wi-Fi
- Data logging to an SD card

## What I Learned

- Electromagnetic induction and resonant circuit tuning
- Power electronics for wireless power transfer
- Sensor interfacing and calibration
- Embedded control with safety interlocks

## Acknowledgments

- MIET Meerut for laboratory facilities and faculty guidance
- My co-authors on the JETIR paper
- The Arduino community for documentation and libraries

---

**Project year:** 2025 · **Stack:** Arduino, Embedded C, power electronics, wireless power transfer · **Status:** completed prototype

Built by [Aryan Panwar](https://aryanpanwar.in).
