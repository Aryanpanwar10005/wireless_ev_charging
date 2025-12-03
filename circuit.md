# Circuit Diagram & Connections

## Pin Configuration

### Arduino Connections

| Component | Pin | Notes |
|-----------|-----|-------|
| IR Sensor | Digital Pin 2 | Active LOW detection |
| Relay Module | Digital Pin 7 | Controls charging circuit |
| Charging LED | Digital Pin 8 | Indicates charging status |
| Ready LED | Digital Pin 9 | System ready indicator |
| Buzzer | Digital Pin 10 | Audio alerts |
| Voltage Sensor | Analog Pin A0 | Via voltage divider |
| Current Sensor | Analog Pin A1 | ACS712 module |

### LCD Display (16x2)

| LCD Pin | Arduino Pin | Function |
|---------|-------------|----------|
| RS | 12 | Register Select |
| E | 11 | Enable |
| D4 | 5 | Data bit 4 |
| D5 | 4 | Data bit 5 |
| D6 | 3 | Data bit 6 |
| D7 | 6 | Data bit 7 |
| VSS | GND | Ground |
| VDD | 5V | Power |
| V0 | 10K Pot | Contrast adjustment |
| A | 5V via 220Ω | Backlight + |
| K | GND | Backlight - |

## Power Supply

- **Main Power:** 12V DC adapter
- **Arduino Power:** Via Vin pin or USB
- **Logic Level:** 5V for all digital components

## Voltage Divider Circuit
```
Input Voltage → R1 (10KΩ) → A0 → R2 (2KΩ) → GND
```

**Calculation:** Output = Input × (R2 / (R1 + R2))

## Current Sensor (ACS712)

- **Model:** ACS712-5A or ACS712-20A
- **VCC:** 5V
- **GND:** GND
- **OUT:** A1
- **Sensitivity:** 185mV/A (5A version) or 100mV/A (20A version)

## IPT Coils

### Transmitter Coil
- Copper wire gauge: 18-22 AWG
- Number of turns: ~20 turns
- Diameter: 10-15 cm
- Connected to power circuit via relay

### Receiver Coil
- Copper wire gauge: 18-22 AWG
- Number of turns: ~20 turns
- Diameter: 10-15 cm
- Connected to rectifier and load

## Resonant Circuit

- **Capacitors:** High-Q capacitors for resonance
- **Frequency:** ~85 kHz
- **Formula:** f = 1 / (2π√(LC))

## Safety Components

1. **Fuse:** In main power line (rated for max current)
2. **Relay:** 5V relay module for isolation
3. **Diodes:** 1N4007 or similar for rectification
4. **Heat Sinks:** For power MOSFETs if needed

## Assembly Notes

- Keep high-current wiring short and thick
- Use proper insulation for all connections
- Ensure coil alignment for maximum efficiency
- Add heat sinks to components that get warm
- Use shielded cables to reduce EMI
- Test with low power before full operation

## Safety Warnings

⚠️ **IMPORTANT:**
- Never touch circuits while powered on
- Use proper fuses and circuit breakers
- Test in a controlled environment
- Monitor temperature during operation
- Keep flammable materials away
- Adult supervision required

## Troubleshooting

| Issue | Possible Cause | Solution |
|-------|----------------|----------|
| No LCD display | Wrong connections | Check pin wiring |
| IR not detecting | Wrong sensor type | Use active LOW sensor |
| Low efficiency | Coil misalignment | Adjust coil position |
| Overcurrent trips | Short circuit | Check all connections |
| No charging | Relay not working | Test relay separately |
