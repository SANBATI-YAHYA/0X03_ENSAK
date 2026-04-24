# Arduino Uno - Ultrasonic Sensor (HC-SR04) Test

## Project Overview
This is a PlatformIO project for testing the HC-SR04 ultrasonic distance sensor with Arduino Uno.

## Hardware Required
- Arduino Uno microcontroller
- HC-SR04 Ultrasonic Distance Sensor
- USB Cable (USB-B) for programming and serial monitoring
- Jumper wires
- Breadboard (optional)

## Wiring Diagram

```
HC-SR04 Ultrasonic Sensor
├─ VCC     → Arduino 5V
├─ GND     → Arduino GND
├─ TRIG    → Arduino Pin 9
└─ ECHO    → Arduino Pin 10
```

## Pin Configuration
| HC-SR04 | Arduino Uno |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| TRIG    | Pin 9       |
| ECHO    | Pin 10      |

## How It Works
1. **Trigger**: A 10 microsecond pulse is sent to TRIG pin
2. **Measure**: The sensor emits ultrasonic sound waves
3. **Echo**: The reflected signal returns to ECHO pin
4. **Calculate**: Distance is calculated from the echo duration
5. **Display**: Results shown on Serial Monitor (9600 baud)

## Distance Calculation
```
Distance (cm) = Echo_Duration (μs) × 0.0343 / 2
Distance (inches) = Distance (cm) / 2.54
```

## Building & Uploading

### Using PlatformIO CLI:
```bash
# Build the project
platformio run

# Upload to Arduino
platformio run --target upload

# Monitor serial output
platformio device monitor --baud 9600
```

### Using PlatformIO IDE (VS Code):
1. Click "Build" (✓ icon)
2. Click "Upload" (→ icon)
3. Click "Serial Monitor" (plug icon) to view output

## Configuration
Edit `platformio.ini` to match your COM port:
- Change `upload_port = COM3` to your Arduino's COM port
- Change `monitor_port = COM3` to match upload port
- Common ports: COM1, COM3, COM4, COM5 (Windows)

## Expected Output
```
=================================
Ultrasonic Sensor Test Started
Arduino Uno - HC-SR04 Sensor
=================================
Distance: 25.50 cm
Distance: 10.04 inches
Echo Duration: 1485 μs
---
```

## Troubleshooting

| Issue | Solution |
|-------|----------|
| No output | Check USB cable connection and COM port in platformio.ini |
| "ERROR: No echo received" | Verify ECHO pin connection and sensor placement |
| Incorrect distance readings | Ensure sensor is not blocked and temperature is normal |
| Compilation error | Verify platformio.ini has correct board: uno |

## Notes
- Sensor range: 2cm to 400cm
- Operating frequency: 40kHz
- Accuracy: ±3mm typical
- Temperature affects accuracy (speed of sound changes with temperature)
