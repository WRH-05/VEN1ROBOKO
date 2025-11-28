#include <Arduino.h>
#include <AFMotor.h>

const int trigPin = 2;       // Shared Trigger D2
const int echoPinFront = A0; // Front Echo A0
const int echoPinLeft = A5;  // Left Echo A5
const int echoPinRight = A1; // Right Echo A1

// Motor setup
AF_DCMotor motorLeft1(1);   // M1 - Left front
AF_DCMotor motorRight1(2);  // M2 - Right front
AF_DCMotor motorRight2(3);  // M3 - Right rear
AF_DCMotor motorLeft2(4);   // M4 - Left rear

void setup() {
  Serial.begin(9600);
  delay(1000); // Wait for serial to stabilize after bootloader
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT);
  
  // Set initial motor speed
  motorLeft1.setSpeed(255);
  motorRight1.setSpeed(255);
  motorRight2.setSpeed(255);
  motorLeft2.setSpeed(255);
  
  Serial.println("Triple Ultrasonic Sensor Test Started");
}

long readDistance(int echoPin) {
  // Clear the trigPin and wait for any previous echo to settle
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin with timeout of 30ms (max ~5m range)
  long duration = pulseIn(echoPin, HIGH, 30000);
  
  // If timeout (duration == 0), return -1 to indicate error
  if (duration == 0) {
    return -1;
  }
  
  // Calculate distance
  return duration * 0.034 / 2;
}

void loop() {
  // Read Front Sensor
  long distFront = readDistance(echoPinFront);
  
  // Delay to prevent echo interference between readings
  delay(60); 

  // Read Right Sensor
  long distRight = readDistance(echoPinRight);
  
  // Delay to prevent echo interference
  delay(60);
  
  // Read Left Sensor
  long distLeft = readDistance(echoPinLeft);

  // Print results
  Serial.print("Front: ");
  if (distFront == -1) {
    Serial.print("Error");
    distFront = 999; // Set to high value if error
  } else {
    Serial.print(distFront);
    Serial.print(" cm");
  }
  
  Serial.print(" | Right: ");
  if (distRight == -1) {
    Serial.print("Error");
    distRight = 999; // Set to high value if error
  } else {
    Serial.print(distRight);
    Serial.print(" cm");
  }
  
  Serial.print(" | Left: ");
  if (distLeft == -1) {
    Serial.print("Error");
    distLeft = 999; // Set to high value if error
  } else {
    Serial.print(distLeft);
    Serial.print(" cm");
  }
  Serial.println();

  // Find closest sensor and distance
  long minDist = distFront;
  String direction = "FRONT";
  
  if (distRight < minDist) {
    minDist = distRight;
    direction = "RIGHT";
  }
  
  if (distLeft < minDist) {
    minDist = distLeft;
    direction = "LEFT";
  }

  // Motor control logic
  if (minDist < 77) { // Less than 770mm (77cm)
    // Move towards closest object at max speed
    motorLeft1.setSpeed(255);
    motorRight1.setSpeed(255);
    motorRight2.setSpeed(255);
    motorLeft2.setSpeed(255);
    
    if (direction == "FRONT") {
      // Move forward
      motorLeft1.run(FORWARD);
      motorRight1.run(FORWARD);
      motorRight2.run(FORWARD);
      motorLeft2.run(FORWARD);
      Serial.println("Action: Moving FORWARD");
    } else if (direction == "RIGHT") {
      // Turn right
      motorLeft1.run(FORWARD);
      motorLeft2.run(FORWARD);
      motorRight1.run(BACKWARD);
      motorRight2.run(BACKWARD);
      Serial.println("Action: Turning RIGHT");
    } else if (direction == "LEFT") {
      // Turn left
      motorLeft1.run(BACKWARD);
      motorLeft2.run(BACKWARD);
      motorRight1.run(FORWARD);
      motorRight2.run(FORWARD);
      Serial.println("Action: Turning LEFT");
    }
  } else {
    // No object detected below 770mm, rotate slowly
    motorLeft1.setSpeed(50);
    motorRight1.setSpeed(50);
    motorRight2.setSpeed(50);
    motorLeft2.setSpeed(50);
    motorLeft1.run(FORWARD);
    motorLeft2.run(FORWARD);
    motorRight1.run(BACKWARD);
    motorRight2.run(BACKWARD);
    Serial.println("Action: Rotating SLOWLY");
  }

  delay(100);
}
