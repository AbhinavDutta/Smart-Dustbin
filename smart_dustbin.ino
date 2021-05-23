#include <Servo.h>   //servo library
Servo servo;
int trigPin = 5;
int echoPin = 6;
int servoPin = 7;
int led = 10;
long duration, dist, average;

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.write(0);
  delay(100);
  servo.detach();
}

void measure()
{
  digitalWrite(10, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1; //formula to get distance in cm knowing the time between
  //sending out and receiving ultrsonic signals
}
void loop()
{
  measure();
  if ( dist < 15 ) //if any object is closer than 15cm then it is detected as object
  {
    Serial.println("object!");
    servo.attach(servoPin);
    delay(1);
    servo.write(0);   //this opens the lid
    delay(3000);      //keeps the lid open for 3 seconds
    servo.write(150); //closes the lid
    delay(1000);
    servo.detach();
  }
  Serial.println(dist);
  delay(500);
}
