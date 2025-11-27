# ROBOKO - Sumo Robot

A 20cm × 20cm, 1.5kg autonomous sumo robot designed to track and engage opponents.

## Current Configuration

### Hardware
- **Platform**: Arduino-based (PlatformIO)
- **Motors**: 2× TT DC gear motors
- **Motor Driver**: Adafruit Motor Shield V1 (AFMotor library)
  - Motor 1 (M1): Left motor
  - Motor 2 (M2): Right motor
- **Sensors**: 3× HC-SR04 Ultrasonic sensors
  - Front sensor: Trig D2, Echo A0
  - Left sensor: Trig D2, Echo A5
  - Right sensor: Trig D2, Echo A1
  - Shared trigger pin on D2

### Current Behavior
The robot implements an aggressive seek-and-attack strategy:

1. **Search Mode**: When no opponent detected (>77cm range)
   - Rotates slowly (speed 100) to scan arena
   
2. **Attack Mode**: When opponent detected (<77cm range)
   - Charges at max speed (255) toward closest detection
   - Front detection → drives forward
   - Right detection → turns right
   - Left detection → turns left

### Detection Range
- Active sensing range: 77cm (770mm)
- Sensor timeout: 30ms (~5m max range)
- Inter-sensor delay: 60ms (prevents echo interference)

## Planned Features
- Edge detection (ring boundary sensors)
- Collision detection
- Strategy improvements
- Performance tuning

## Build & Upload
```bash
platformio run --target upload
platformio device monitor
```

## Competition Class
- **Size**: 20cm × 20cm
- **Weight**: 1.5kg
- **Ring**: Standard sumo ring (154cm diameter)
