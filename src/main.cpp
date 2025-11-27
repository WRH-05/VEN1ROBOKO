#include <Arduino.h>

const int trigPin = 2;       // Shared Trigger D2
const int echoPinFront = A0; // Front Echo A0
const int echoPinRight = A1; // Right Echo A1

void setup() {
  Serial.begin(9600);
  delay(1000); // Wait for serial to stabilize after bootloader
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(echoPinRight, INPUT);
  Serial.println("Dual Ultrasonic Sensor Test Started");
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

  // Print results
  Serial.print("Front: ");
  if (distFront == -1) {
    Serial.print("Error");
  } else {
    Serial.print(distFront);
    Serial.print(" cm");
  }
  
  Serial.print(" | Right: ");
  if (distRight == -1) {
    Serial.print("Error");
  } else {
    Serial.print(distRight);
    Serial.print(" cm");
  }
  Serial.println();

  delay(500);
}
