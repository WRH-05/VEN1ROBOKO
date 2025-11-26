#include <AFMotor.h>   

AF_DCMotor motor1(1);     
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);     
AF_DCMotor motor4(4);

int trigPin = 9;
int echoPin = 10;
int S0 = 2;
int S1 = 3;
int S2 = 4;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);

  delay(5000);             
  
  motor1.setSpeed(255);    
  motor2.setSpeed(255);   
  motor3.setSpeed(255);    
  motor4.setSpeed(255);  
}

void loop() {
  robot();
}

// ---------- CAPTEURS DISTANCE ----------
int distance(int sensor) {
  // sensor = 0, 1 ou 2 (selon le capteur à lire)
  long duration;
  int dist;

  // Sélection du capteur via multiplexeur
  digitalWrite(S0, sensor & 0x01);
  digitalWrite(S1, (sensor >> 1) & 0x01);
  digitalWrite(S2, (sensor >> 2) & 0x01);
  delay(2);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); 
  dist = duration * 0.034 / 2;

  if (duration == 0) dist = 999;  // si rien détecté

  return dist;
}

// ---------- MOUVEMENTS DE BASE ----------

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turnleft() {
  // Tourne sur place vers la gauche :
  // moteurs gauche en arrière, moteurs droite en avant
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(300);   // durée du virage à ajuster
  stopMotors();
}

void turnright() {
  // Tourne sur place vers la droite :
  // moteurs gauche en avant, moteurs droite en arrière
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(300);   // durée du virage à ajuster
  stopMotors();
}

// ---------- LOGIQUE ROBOT ----------

void robot() {
  int d1 = distance(0); 
  int d2 = distance(1);
  int d3 = distance(2);

  // À adapter selon comment sont placés tes capteurs
  if (d1 < 30 && d2 > 30 && d3 > 30 ) {
    // Exemple : obstacle devant capteur 1 → avance tout droit
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  } else if (d1 > 30 && d2 < 30 && d3 > 30) {
    // obstacle au milieu → tourne à droite
    turnright();
  } else if (d1 > 30 && d2 > 30 && d3 < 30) {
    turnleft();
  } else {
    NoDetect();
  }
}



void NoDetect() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(200);
  stopMotors();

  char b = border();

  switch (b) {
    case 'R': 
      motor1.setSpeed(250);    
      motor2.setSpeed(100);   
      motor3.setSpeed(250);    
      motor4.setSpeed(100);
      break;

    case 'G':   
      motor1.setSpeed(100);    
      motor2.setSpeed(200);   
      motor3.setSpeed(100);    
      motor4.setSpeed(200);
      break;

    default:
      motor1.setSpeed(200);    
      motor2.setSpeed(200);   
      motor3.setSpeed(200);    
      motor4.setSpeed(200);
      break;
  }

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

char border() {
  return 'N';
}
