/*
 * ========================================================================
 * WIRELESS EV CHARGING SYSTEM USING INDUCTIVE POWER TRANSFER (IPT)
 * ========================================================================
 * 
 * Author: Aryan Panwar
 * Institution: MIET Meerut
 * Year: 2025
 * 
 * Description:
 * This project implements a wireless charging system for electric vehicles
 * using Inductive Power Transfer (IPT) technology, with automated vehicle
 * detection and real-time monitoring.
 * 
 * Features:
 * - Automated vehicle detection using IR sensors
 * - Real-time monitoring via 16x2 LCD display
 * - Wireless power transfer using resonant inductive coupling
 * - Efficiency display (a simulated placeholder until input and output power are measured)
 * - Safety features with automatic shutdown
 * 
 * License: MIT License
 * GitHub: https://github.com/Aryanpanwar10005/wireless-ev-charging
 * ========================================================================
 */

#include <LiquidCrystal.h>

// ==================== PIN DEFINITIONS ====================
const int IR_SENSOR_PIN = 2;       // IR sensor for vehicle detection
const int RELAY_PIN = 7;           // Relay to control charging circuit
const int VOLTAGE_SENSOR_PIN = A0; // Analog pin for voltage monitoring
const int CURRENT_SENSOR_PIN = A1; // Analog pin for current monitoring
const int LED_CHARGING = 8;        // LED indicator for charging status
const int LED_READY = 9;           // LED indicator for system ready
const int BUZZER_PIN = 10;         // Buzzer for alerts (optional)

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

// ==================== CONFIGURATION ====================
// Calibration constants (adjust based on your hardware)
const float VOLTAGE_CALIBRATION = 5.0 / 1023.0;  // ADC to voltage conversion
const float CURRENT_CALIBRATION = 5.0 / 1023.0;  // ADC to current conversion
const float VOLTAGE_DIVIDER_RATIO = 5.0;         // Voltage divider ratio
const float CURRENT_SENSOR_SENSITIVITY = 0.185;  // For ACS712-5A (185mV/A)
const float CURRENT_SENSOR_OFFSET = 2.5;         // ACS712 offset voltage

// System parameters
const int DETECTION_DELAY = 1000;      // Wait time before starting charging (ms)
const int UPDATE_INTERVAL = 500;       // Display update interval (ms)
const float MIN_VOLTAGE = 3.0;         // Minimum voltage to start charging
const float MAX_CURRENT = 3.0;         // Maximum safe current (A)
const float TARGET_EFFICIENCY = 85.0;  // Target efficiency (%)

// ==================== GLOBAL VARIABLES ====================
bool vehicleDetected = false;
bool chargingActive = false;
float inputVoltage = 0.0;
float outputVoltage = 0.0;
float current = 0.0;
float power = 0.0;
float efficiency = 0.0;
unsigned long lastUpdateTime = 0;
unsigned long chargingStartTime = 0;
unsigned long totalChargingTime = 0;

// ==================== SETUP ====================
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println(F("========================================"));
  Serial.println(F("Wireless EV Charging System"));
  Serial.println(F("Initializing..."));
  Serial.println(F("========================================"));
  
  // Initialize LCD
  lcd.begin(16, 2);
  displayWelcome();
  
  // Initialize pins
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_CHARGING, OUTPUT);
  pinMode(LED_READY, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initial states
  digitalWrite(RELAY_PIN, LOW);      // Charging off
  digitalWrite(LED_CHARGING, LOW);   // Charging LED off
  digitalWrite(LED_READY, HIGH);     // Ready LED on
  
  // System ready
  Serial.println(F("System initialized successfully"));
  Serial.println(F("Waiting for vehicle detection..."));
  Serial.println();
  
  delay(2000);
  lcd.clear();
}

// ==================== MAIN LOOP ====================
void loop() {
  // Check for vehicle detection
  vehicleDetected = digitalRead(IR_SENSOR_PIN) == LOW; // Active LOW sensor
  
  // State machine
  if (vehicleDetected && !chargingActive) {
    // Vehicle detected, prepare to start charging
    delay(DETECTION_DELAY); // Debounce and confirmation delay
    if (digitalRead(IR_SENSOR_PIN) == LOW) { // Confirm detection
      startCharging();
    }
  } 
  else if (!vehicleDetected && chargingActive) {
    // Vehicle removed, stop charging
    stopCharging();
  }
  
  // Update display and readings at regular intervals
  if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
    lastUpdateTime = millis();
    
    if (chargingActive) {
      // Read sensor values
      readSensors();
      
      // Calculate efficiency
      calculateEfficiency();
      
      // Safety checks
      performSafetyChecks();
      
      // Update display
      updateDisplay();
      
      // Send data to serial monitor
      sendSerialData();
      
      // Calculate charging duration
      totalChargingTime = (millis() - chargingStartTime) / 1000; // in seconds
    } 
    else {
      // Display waiting message
      displayWaiting();
    }
  }
}

// ==================== CHARGING CONTROL ====================
void startCharging() {
  chargingActive = true;
  chargingStartTime = millis();
  
  // Turn on charging circuit
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_CHARGING, HIGH);
  digitalWrite(LED_READY, LOW);
  
  // Beep to indicate start
  beep(2);
  
  // Display message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Charging");
  lcd.setCursor(0, 1);
  lcd.print("   Started!");
  delay(1500);
  
  Serial.println(F("========================================"));
  Serial.println(F("CHARGING STARTED"));
  Serial.println(F("========================================"));
}

void stopCharging() {
  chargingActive = false;
  
  // Turn off charging circuit
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_CHARGING, LOW);
  digitalWrite(LED_READY, HIGH);
  
  // Beep to indicate stop
  beep(1);
  
  // Display summary
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Charging Stopped");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(totalChargingTime);
  lcd.print("s");
  delay(3000);
  
  Serial.println(F("========================================"));
  Serial.println(F("CHARGING STOPPED"));
  Serial.print(F("Total Duration: "));
  Serial.print(totalChargingTime);
  Serial.println(F(" seconds"));
  Serial.print(F("Average Efficiency: "));
  Serial.print(efficiency);
  Serial.println(F("%"));
  Serial.println(F("========================================"));
  Serial.println();
}

// ==================== SENSOR READING ====================
void readSensors() {
  // Read voltage using voltage divider
  int voltageRaw = analogRead(VOLTAGE_SENSOR_PIN);
  inputVoltage = voltageRaw * VOLTAGE_CALIBRATION * VOLTAGE_DIVIDER_RATIO;
  
  // Smooth voltage reading (simple averaging)
  static float voltageSum = 0;
  static int voltageCount = 0;
  voltageSum += inputVoltage;
  voltageCount++;
  if (voltageCount >= 5) {
    inputVoltage = voltageSum / 5.0;
    voltageSum = 0;
    voltageCount = 0;
  }
  
  // Read current using ACS712 sensor
  int currentRaw = analogRead(CURRENT_SENSOR_PIN);
  float voltage = currentRaw * VOLTAGE_CALIBRATION;
  current = (voltage - CURRENT_SENSOR_OFFSET) / CURRENT_SENSOR_SENSITIVITY;
  
  // Handle negative current readings (noise)
  if (current < 0) current = 0;
  
  // Smooth current reading
  static float currentSum = 0;
  static int currentCount = 0;
  currentSum += current;
  currentCount++;
  if (currentCount >= 5) {
    current = currentSum / 5.0;
    currentSum = 0;
    currentCount = 0;
  }
  
  // Calculate power
  power = inputVoltage * current;
}

void calculateEfficiency() {
  // For demonstration: simulate efficiency based on power transfer
  // In real implementation, measure both input and output power
  // efficiency = (output_power / input_power) * 100
  
  if (power > 0.1) {
    // Simulated efficiency with some variation
    efficiency = 82.0 + random(0, 7); // Range: 82-88%
    
    // Add realistic variations based on power level
    if (power < 2.0) {
      efficiency -= 5; // Lower efficiency at low power
    }
  } else {
    efficiency = 0;
  }
  
  // Ensure efficiency is within valid range
  if (efficiency > 100.0) efficiency = 100.0;
  if (efficiency < 0) efficiency = 0;
}

// ==================== SAFETY CHECKS ====================
void performSafetyChecks() {
  // Check for over-current
  if (current > MAX_CURRENT) {
    emergencyStop("OVER CURRENT!");
  }
  
  // Check for abnormal voltage
  if (inputVoltage < MIN_VOLTAGE && chargingActive) {
    emergencyStop("LOW VOLTAGE!");
  }
  
  // Check for overheating (if temperature sensor is added)
  // Add temperature check here if needed
}

void emergencyStop(const char* reason) {
  // Immediate shutdown
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_CHARGING, LOW);
  chargingActive = false;
  
  // Alert
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EMERGENCY STOP!");
  lcd.setCursor(0, 1);
  lcd.print(reason);
  
  // Continuous beeping
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
  
  Serial.println(F("========================================"));
  Serial.println(F("EMERGENCY STOP ACTIVATED!"));
  Serial.print(F("Reason: "));
  Serial.println(reason);
  Serial.println(F("========================================"));
  
  delay(5000);
  digitalWrite(LED_READY, HIGH);
}

// ==================== DISPLAY FUNCTIONS ====================
void displayWelcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Wireless EV");
  lcd.setCursor(0, 1);
  lcd.print("  Charging");
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  System v1.0");
  lcd.setCursor(0, 1);
  lcd.print("  By: Aryan");
  delay(2000);
}

void displayWaiting() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");
  
  // Blinking ready indicator
  static bool ledState = false;
  ledState = !ledState;
  digitalWrite(LED_READY, ledState);
}

void updateDisplay() {
  // Line 1: Voltage and Current
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(inputVoltage, 1);
  lcd.print("V ");
  lcd.print("I:");
  lcd.print(current, 2);
  lcd.print("A");
  
  // Line 2: Power and Efficiency
  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(power, 1);
  lcd.print("W ");
  lcd.print("E:");
  lcd.print(efficiency, 0);
  lcd.print("%");
}

// ==================== SERIAL OUTPUT ====================
void sendSerialData() {
  Serial.print(F("Time: "));
  Serial.print(totalChargingTime);
  Serial.print(F("s | V: "));
  Serial.print(inputVoltage, 2);
  Serial.print(F("V | I: "));
  Serial.print(current, 3);
  Serial.print(F("A | P: "));
  Serial.print(power, 2);
  Serial.print(F("W | Eff: "));
  Serial.print(efficiency, 1);
  Serial.println(F("%"));
}

// ==================== UTILITY FUNCTIONS ====================
void beep(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

/*
 * ========================================================================
 * IMPLEMENTATION NOTES
 * ========================================================================
 * 
 * CALIBRATION:
 * - Adjust VOLTAGE_DIVIDER_RATIO based on your resistor values
 * - Calibrate current sensor using a known current source
 * - Test with multimeter and adjust calibration constants
 * 
 * HARDWARE CONNECTIONS:
 * - IR Sensor: Pin 2 (Active LOW)
 * - Relay: Pin 7
 * - LCD: Pins 12, 11, 5, 4, 3, 6
 * - Voltage Sensor: A0
 * - Current Sensor: A1
 * - Charging LED: Pin 8
 * - Ready LED: Pin 9
 * - Buzzer: Pin 10
 * 
 * SAFETY:
 * - Always test with low power first
 * - Monitor temperature during operation
 * - Keep emergency stop accessible
 * - Use proper insulation
 * 
 * OPTIMIZATION:
 * - Tune resonant frequency for maximum efficiency
 * - Optimize coil distance (2-5cm typical)
 * - Ensure perfect coil alignment
 * - Use high-Q capacitors
 * 
 * ========================================================================
 */
