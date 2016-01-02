#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  9   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10   // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;
int angle;
int angleStep;

int angleStepDelayInMs=50;

void setup() {
  angle=0;
  angleStep=1;
  Serial.begin(9600);
  myservo.attach(12);
}

void loop() {
    alterServoMoveDirection();

    Serial.print(angle);
    Serial.print("|");
    Serial.print(sonar.ping_cm());
    Serial.println();

    angle+=angleStep;
    myservo.write(angle);
    delay(angleStepDelayInMs);
}

void alterServoMoveDirection()
{
  if(angle==180)
  {
    angleStep=-1;  
  }
  else if (angle==0)
  {
    angleStep=1;  
  } 
}

