/* ============================================
   3 SERVO MOTORS - SEQUENTIAL MOVEMENT TEST
   PCA9685 PWM Driver
   Servo Pins: 0, 2, 4 (on PCA9685)
   
   SEQUENCE:
   Step 1: S0(110°) S2(90°) S4(90°) - 3s each → Wait 2s
   Step 2: S0(110°) S2(40°) S4(130°) - 3s each → Wait 2s
   Step 3: S0(110°) S2(90°) S4(90°) - 3s each → Wait 2s
   Step 4: S0(180°) S2(50°) S4(130°) - 3s each → Wait 2s
   Step 5: S0(110°) S2(90°) S4(90°) - 3s each → Wait 2s
   REPEAT...
   ============================================ */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// -------- PCA9685 SERVO DRIVER --------
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// -------- PWM VALUES FOR SERVO --------
#define SERVOMIN 150    // 0 degrees
#define SERVOMAX 600    // 180 degrees

// -------- SERVO POSITIONS (5 Steps) --------
#define S0_POS1 110
#define S0_POS2 110
#define S0_POS3 110
#define S0_POS4 180
#define S0_POS5 110

#define S2_POS1 90
#define S2_POS2 40
#define S2_POS3 90
#define S2_POS4 50
#define S2_POS5 90

#define S4_POS1 90
#define S4_POS2 130
#define S4_POS3 90
#define S4_POS4 130
#define S4_POS5 90

void setup()
{
  Serial.begin(9600);
  Serial.println("\n================================");
  Serial.println("3 SERVO SEQUENTIAL MOVEMENT");
  Serial.println("PCA9685 PWM Driver");
  Serial.println("================================");
  Serial.println("Servo 0 (S0) → Pin 0");
  Serial.println("Servo 2 (S2) → Pin 2");
  Serial.println("Servo 4 (S4) → Pin 4");
  Serial.println("================================\n");
  
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(10);
  
  // Set all servos to center position (90°)
  pwm.setPWM(0, 0, angleToMicros(90));
  pwm.setPWM(2, 0, angleToMicros(90));
  pwm.setPWM(4, 0, angleToMicros(90));
  delay(500);
  
  Serial.println("✓ PCA9685 initialized");
  Serial.println("✓ All servos set to 90°");
  Serial.println("✓ Starting sequence...\n");
}

// Maps an angle (0-180°) to a PWM value
int angleToMicros(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

// Moves a servo smoothly over a specified duration
// pin: servo pin on PCA9685
// from: starting angle
// to: target angle
// durationMS: total movement time in milliseconds
void moveServoSmooth(int pin, int from, int to, unsigned long durationMS) {
  unsigned long startTime = millis();
  
  while (millis() - startTime < durationMS) {
    long elapsed = millis() - startTime;
    float progress = (float)elapsed / durationMS;
    
    // Calculate current angle based on progress
    int currentAngle;
    if (to > from) {
      currentAngle = from + (int)(progress * (to - from));
    } else {
      currentAngle = from - (int)(progress * (from - to));
    }
    
    pwm.setPWM(pin, 0, angleToMicros(currentAngle));
    delay(15);  // Update every 15ms for smooth motion
  }
  
  // Ensure we reach exact target
  pwm.setPWM(pin, 0, angleToMicros(to));
}

// Display current step information
void printStep(int stepNum, int s0Angle, int s2Angle, int s4Angle, int duration) {
  Serial.print("=== STEP ");
  Serial.print(stepNum);
  Serial.println(" ===");
  Serial.print("S0 → ");
  Serial.print(s0Angle);
  Serial.print("° (");
  Serial.print(duration);
  Serial.println("s)");
}

void loop() {
  // ========== STEP 1 (3 seconds each) ==========
  Serial.println("\n┌─ STEP 1 ─ 3 seconds per servo ─┐");
  Serial.println("Position: S0=110° | S2=90° | S4=90°\n");
  
  // Move S0 to position 1 (3 seconds)
  Serial.println("▶ S0 moving to 110°...");
  moveServoSmooth(0, 90, S0_POS1, 3000);
  Serial.println("✓ S0 reached 110°\n");
  
  // Move S2 to position 1 (3 seconds)
  Serial.println("▶ S2 moving to 90°...");
  moveServoSmooth(2, 90, S2_POS1, 3000);
  Serial.println("✓ S2 reached 90°\n");
  
  // Move S4 to position 1 (3 seconds)
  Serial.println("▶ S4 moving to 90°...");
  moveServoSmooth(4, 90, S4_POS1, 3000);
  Serial.println("✓ S4 reached 90°\n");
  
  // Wait 2 seconds
  Serial.println("⏸ Waiting 2 seconds...");
  delay(2000);
  Serial.println("└─────────────────────────────────┘\n");

  // ========== STEP 2 (3 seconds each) ==========
  Serial.println("┌─ STEP 2 ─ 3 seconds per servo ─┐");
  Serial.println("Position: S0=110° | S2=40° | S4=130°\n");
  
  // Move S0 to position 2 (3 seconds)
  Serial.println("▶ S0 moving to 110°...");
  moveServoSmooth(0, S0_POS1, S0_POS2, 3000);
  Serial.println("✓ S0 reached 110°\n");
  
  // Move S2 to position 2 (3 seconds)
  Serial.println("▶ S2 moving to 40°...");
  moveServoSmooth(2, S2_POS1, S2_POS2, 3000);
  Serial.println("✓ S2 reached 40°\n");
  
  // Move S4 to position 2 (3 seconds)
  Serial.println("▶ S4 moving to 130°...");
  moveServoSmooth(4, S4_POS1, S4_POS2, 3000);
  Serial.println("✓ S4 reached 130°\n");
  
  // Wait 2 seconds
  Serial.println("⏸ Waiting 2 seconds...");
  delay(2000);
  Serial.println("└─────────────────────────────────┘\n");

  // ========== STEP 3 (3 seconds each) ==========
  Serial.println("┌─ STEP 3 ─ 3 seconds per servo ─┐");
  Serial.println("Position: S0=110° | S2=90° | S4=90°\n");
  
  // Move S0 to position 3 (3 seconds)
  Serial.println("▶ S0 moving to 110°...");
  moveServoSmooth(0, S0_POS2, S0_POS3, 3000);
  Serial.println("✓ S0 reached 110°\n");
  
  // Move S2 to position 3 (3 seconds)
  Serial.println("▶ S2 moving to 90°...");
  moveServoSmooth(2, S2_POS2, S2_POS3, 3000);
  Serial.println("✓ S2 reached 90°\n");
  
  // Move S4 to position 3 (3 seconds)
  Serial.println("▶ S4 moving to 90°...");
  moveServoSmooth(4, S4_POS2, S4_POS3, 3000);
  Serial.println("✓ S4 reached 90°\n");
  
  // Wait 2 seconds
  Serial.println("⏸ Waiting 2 seconds...");
  delay(2000);
  Serial.println("└─────────────────────────────────┘\n");

  // ========== STEP 4 (3 seconds each) ==========
  Serial.println("┌─ STEP 4 ─ 3 seconds per servo ─┐");
  Serial.println("Position: S0=180° | S2=50° | S4=130°\n");
  
  // Move S0 to position 4 (3 seconds)
  Serial.println("▶ S0 moving to 180°...");
  moveServoSmooth(0, S0_POS3, S0_POS4, 3000);
  Serial.println("✓ S0 reached 180°\n");
  
  // Move S2 to position 4 (3 seconds)
  Serial.println("▶ S2 moving to 50°...");
  moveServoSmooth(2, S2_POS3, S2_POS4, 3000);
  Serial.println("✓ S2 reached 50°\n");
  
  // Move S4 to position 4 (3 seconds)
  Serial.println("▶ S4 moving to 130°...");
  moveServoSmooth(4, S4_POS3, S4_POS4, 3000);
  Serial.println("✓ S4 reached 130°\n");
  
  // Wait 2 seconds
  Serial.println("⏸ Waiting 2 seconds...");
  delay(2000);
  Serial.println("└─────────────────────────────────┘\n");

  // ========== STEP 5 (3 seconds each) - FINAL RETURN (REVERSE ORDER) ==========
  Serial.println("┌─ STEP 5 ─ 3 seconds per servo ─┐");
  Serial.println("Position: S0=110° | S2=90° | S4=90° (Reverse Order)\n");
  
  // Move S2 to position 5 FIRST (3 seconds)
  Serial.println("▶ S2 moving to 90°...");
  moveServoSmooth(2, S2_POS4, S2_POS5, 3000);
  Serial.println("✓ S2 reached 90°\n");
  
  // Move S4 to position 5 SECOND (3 seconds)
  Serial.println("▶ S4 moving to 90°...");
  moveServoSmooth(4, S4_POS4, S4_POS5, 3000);
  Serial.println("✓ S4 reached 90°\n");
  
  // Move S0 to position 5 LAST (3 seconds)
  Serial.println("▶ S0 moving to 110°...");
  moveServoSmooth(0, S0_POS4, S0_POS5, 3000);
  Serial.println("✓ S0 reached 110°\n");
  
  // Wait 2 seconds
  Serial.println("⏸ Waiting 2 seconds...");
  delay(2000);
  Serial.println("└─────────────────────────────────┘\n");
  
  // REPEAT: Loop starts again (continuous cycle)
  Serial.println("↻ CYCLE COMPLETE - Repeating...\n");
  delay(1000);
}

/* ============================================
   HARDWARE CONNECTIONS:
   
   PCA9685 to Arduino:
   - SDA → A4
   - SCL → A5
   - VCC → 5V
   - GND → GND
   
   Servos to PCA9685:
   - Servo 0 Signal → Pin 0
   - Servo 2 Signal → Pin 2
   - Servo 4 Signal → Pin 4
   - All Servo GND → PCA9685 GND (common)
   - All Servo VCC → External 5V Power Supply
   ============================================ */