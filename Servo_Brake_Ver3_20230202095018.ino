#include <Servo.h>

// aim of this programme is to brake (rotate 90 deg) when the ultrasonic distance reaches a certain DISTANCE_THRESHOLD away from the launcher.
// the servo motor will be attached to a small foam block that will move down to slow the launcher. this could be used either as a primary control mechanism 
// or as a redundancy just to ensure the car doesn't go batshit

const int TRIG_PIN  = 6; const int ECHO_PIN  = 7;  const int SERVO_PIN = 9;
const double DISTANCE_THRESHOLD = 20.0; //cm
const int pulseDuration = 10;

bool brake = false;

Servo servo;

double duration_us, distance_cm; 

void setup() {
  Serial.begin (9600);     
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN); 
  servo.write(0);
}

//Arduino will be responsbiel for both the breaking and the release of the lander. Break it into different fucntions. 
void breakMechanism(double &dist);
void releaseMechanism(double &dist);

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(pulseDuration);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  
  distance_cm = 0.017 * duration_us; //0.017 is a magic number, anyway to automate the calculation of this number? 

  if((distance_cm > DISTANCE_THRESHOLD) && !brake) {
      servo.write(90); // rotate servo motor to 90 degree
      brake = true;
  }
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
