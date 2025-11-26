#include <AFMotor.h>
#include <Arduino.h>

AF_DCMotor motor1(1);     
AF_DCMotor motor2(2);

void setup() {
  Serial.begin(9600);
  
  motor1.setSpeed(200);    
  motor2.setSpeed(200);   
  
  delay(2000);  // Wait 2 seconds before starting
}

void loop() {
  // Movement sequence: Forward -> Stop -> Backward -> Stop -> Turn -> Repeat
  
  // Move forward for 2 seconds
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(2000);
  
  // Stop for 1 second
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(1000);
  
  // Move backward for 1.5 seconds
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(1500);
  
  // Stop for 1 second
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(1000);
  
  // Turn (one motor forward, one backward) for 1 second
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(1000);
  
  // Stop for 1 second
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(1000);
}
