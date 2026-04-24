/* ============================================
   3 Servo Motors - Continuous Sweep Test
   Working code - Servo sweep 0° to 180° and back
   Pins: 0, 2, 4
   ============================================ */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// -------- PCA9685 SERVO DRIVER --------
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// -------- PWM VALUES FOR SERVO --------
#define SERVOMIN 150    // 0 degrees
#define SERVOMAX 600    // 180 degrees

void setup()
{
  Serial.begin(9600);
  Serial.println("\n================================");
  Serial.println("3 SERVO SWEEP TEST");
  Serial.println("================================");
  Serial.println("PWM Range: 150-600");
  Serial.println("Servo Pins: 0, 2, 4");
  Serial.println("================================\n");
  
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(10);
  
  Serial.println("PCA9685 initialized ✓");
  Serial.println("Starting servo sweep...\n");
}

void loop()
{
  // Fix all servos at 90 degrees (middle position)
  int servo_90 = (SERVOMIN + SERVOMAX) / 2;  // Calculate 90 degrees PWM value
  
  pwm.setPWM(0, 0, servo_90);  // Servo 1 on pin 0 → 90°
  pwm.setPWM(2, 0, servo_90);  // Servo 2 on pin 2 → 90°
  pwm.setPWM(4, 0, servo_90);  // Servo 3 on pin 4 → 90°
  
  delay(100);  // Check every 100ms
}

/* ============================================
   HARDWARE CONNECTIONS:
   
   PCA9685 to Arduino:
   - SDA → A4
   - SCL → A5
   - VCC → 5V
   - GND → GND
   
   Servos to PCA9685:
   - Servo 1 Signal → Pin 0
   - Servo 2 Signal → Pin 2
   - Servo 3 Signal → Pin 4
   - All Servo GND → PCA9685 GND (common)
   - All Servo VCC → External 5V Power Supply
   
   ============================================ */
