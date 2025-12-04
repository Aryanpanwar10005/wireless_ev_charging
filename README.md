# Wireless EV Charging System 🔋⚡

A wireless charging prototype for electric vehicles using Inductive Power Transfer (IPT) technology with Arduino microcontroller. This project demonstrates practical implementation of wireless power transfer principles for sustainable transportation solutions.

## ✨ Features

- ⚡ 85% power transfer efficiency
- 🤖 Automated vehicle detection using IR sensors
- 📊 Real-time power monitoring via LCD display
- 🔧 Resonant circuit design for optimal power transfer
- 💡 Smart charging system with automatic start/stop
- 🛡️ Safety features with emergency shutdown
- 📈 Efficiency monitoring and calculation

## 🛠️ Hardware Components

- Arduino Uno/Nano
- Transmitter Coil (Primary)
- Receiver Coil (Secondary)
- IR Sensors (Vehicle Detection)
- 16x2 LCD Display
- 5V Relay Module
- Power MOSFETs
- Capacitors and Inductors for resonant circuit
- ACS712 Current Sensor
- Voltage divider resistors (10KΩ, 2KΩ)
- DC Power Supply (12V)
- Rectifier diodes
- LED indicators
- Buzzer (optional)

## 📋 Software Requirements

- Arduino IDE 1.8+ or 2.0+
- LiquidCrystal Library (built-in with Arduino IDE)

## 📥 Installation

1. Clone this repository
```bash
git clone https://github.com/Aryanpanwar10005/wireless_ev_charging.git
```

2. Open `wireless_ev_charging.ino` in Arduino IDE
3. Select your board: Tools → Board → Arduino Uno
4. Select your COM port: Tools → Port → (your port)
5. Upload to your Arduino board

## 🔌 Circuit Connections

- Connect the transmitter coil to the primary circuit with resonant capacitor
- Connect the receiver coil to the secondary circuit
- Wire IR sensor to Arduino digital pin 2
- Connect 16x2 LCD display to Arduino (pins 12, 11, 5, 4, 3, 6)
- Connect relay module to pin 7 for charging control
- Wire voltage sensor to analog pin A0
- Connect current sensor (ACS712) to analog pin A1
- Ensure proper coil alignment for maximum efficiency

## 🚀 Usage

- Power on the system
- LCD will display "System Ready - Waiting..."
- Place the receiver coil near the transmitter (2-5cm distance)
- IR sensors will detect presence and automatically start charging
- Monitor real-time voltage, current, power, and efficiency on LCD
- System automatically stops when object is removed
- View detailed data on Serial Monitor (9600 baud)

## 📊 Technical Specifications

- Operating Frequency: ~85 kHz (resonant frequency)
- Power Transfer Efficiency: 85% average
- Power Output: Up to 15W
- Detection Range: 5-10cm (IR sensor)
- Coil Distance: Optimal 2-5cm
- Input Voltage: 12V DC
- Maximum Current: 3A (with safety cutoff)

## 🎯 Project Achievements

- Successfully implemented IPT technology using readily available components
- Achieved 85% efficiency through optimized coil design and resonant frequency tuning
- Integrated smart detection and real-time monitoring system
- Demonstrated practical application of wireless power transfer for EV charging
- Implemented safety features including over-current protection and emergency stop

## 🔬 How It Works

The system uses resonant inductive coupling for efficient power transfer:

- **Transmitter Circuit**: High-frequency AC power → Transmitter coil → Magnetic field generation
- **Receiver Circuit**: Magnetic field reception → Receiver coil → AC voltage → Rectification → DC output
- **Resonant Tuning**: Capacitors tuned to match transmitter and receiver frequencies for maximum power transfer
- **Control System**: Arduino monitors and controls the entire charging process

### Key Components Function:
- **Transmitter Coil**: Creates alternating magnetic field
- **Receiver Coil**: Captures magnetic energy and converts to electrical power
- **Resonant Capacitors**: Maximize power transfer at specific frequency
- **Relay**: Controls power flow to charging circuit
- **Sensors**: Monitor voltage, current, and vehicle presence

## 📈 Performance Metrics

- Peak Efficiency: 87%
- Average Efficiency: 85%
- Power Transfer Range: 2-5cm optimal, up to 8cm functional
- Response Time: < 1 second for vehicle detection
- Accuracy: ±2% voltage reading, ±5% current reading

## 🧪 Testing & Validation

- Tested with various coil distances (2cm to 10cm)
- Measured efficiency at different power levels (5W to 15W)
- Validated automated detection system reliability (99% success rate)
- Confirmed stable power delivery under varying load conditions
- Verified safety features respond correctly to fault conditions

## 💡 Learning Outcomes

- Practical understanding of electromagnetic induction principles
- Experience with resonant circuit design and frequency tuning
- Power electronics and efficient energy transfer techniques
- Embedded systems integration and real-time control
- Sensor interfacing and data acquisition
- Implementation of safety features in power systems

## 🚧 Future Enhancements

- Increase power output for faster charging (50W+)
- Implement multiple receiver coils for simultaneous charging
- Add smartphone app for remote monitoring via Bluetooth/WiFi
- Optimize coil design using Finite Element Analysis (FEA)
- Add temperature monitoring and thermal management
- Implement foreign object detection (FOD) for enhanced safety
- Include battery management system (BMS) integration
- Data logging to SD card for analysis
- PID control for stable power delivery

## 🛡️ Safety Features

- Over-current protection (3A maximum)
- Low voltage cutoff
- Emergency stop function
- Visual and audible alerts (LED + Buzzer)
- Automatic shutdown on vehicle removal
- Real-time monitoring and diagnostics

## 👨‍💻 Author

**Aryan Panwar**
- Electronics & Communication Engineering Student
- MIET Meerut (2022-2026)
- 📧 Email: [aryanpanwar10005@gmail.com](mailto:aryanpanwar10005@gmail.com)
- 💼 LinkedIn: [aryan-panwar-b5322b269](https://www.linkedin.com/in/aryan-panwar-b5322b269)
- 🐙 GitHub: [@Aryanpanwar10005](https://github.com/Aryanpanwar10005)

## 🙏 Acknowledgments

- MIET Meerut for laboratory facilities and project support
- Arduino community for excellent documentation and resources
- Open-source community for libraries and tools
- Faculty advisors for guidance and mentorship

## 📞 Contact

For questions, suggestions, or collaboration opportunities:
- Open an issue in this repository
- Email: [aryanpanwar10005@gmail.com](mailto:aryanpanwar10005@gmail.com)
- Connect on LinkedIn

## ⭐ Support

If you found this project interesting or helpful:
- ⭐ Star this repository
- 🔄 Share with others interested in wireless charging technology
- 🐛 Report bugs or suggest improvements
- 🤝 Contribute to the project

---

**Project Year:** 2025  
**Technology Stack:** Arduino | Embedded C | Power Electronics | Wireless Power Transfer  
**Status:** Completed ✅

*"Innovation in wireless power transfer for a sustainable future"*
