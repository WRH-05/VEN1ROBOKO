#include <Arduino.h>

const int trigPin = 2;       // Shared Trigger D2
const int echoPinFront = A0; // Front Echo A0
const int echoPinRight = A1; // Right Echo A1

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(echoPinRight, INPUT);
  Serial.println("Dual Ultrasonic Sensor Test Started");
}

long readDistance(int echoPin) {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance
  return duration * 0.034 / 2;
}

void loop() {
  // Read Front Sensor
  long distFront = readDistance(echoPinFront);
  
  // Small delay to prevent echo interference between readings
  delay(50); 

  // Read Right Sensor
  long distRight = readDistance(echoPinRight);

  // Print results
  Serial.print("Front: ");
  Serial.print(distFront);
  Serial.print(" cm | Right: ");
  Serial.print(distRight);
  Serial.println(" cm");

  delay(500);
}
