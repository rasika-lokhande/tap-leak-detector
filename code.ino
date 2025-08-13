// Arduino based tap Leak Detector

// Initializing Ultrasonic Sensor
const int trigPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor
int redled = 5;        // Red LED pin

// Initializing Servo Motor
#include <Servo.h>  
int servoPin = 4;      // Servo motor pin
Servo servo;           // Servo object
int servoAngle = 0;    // servo position in degrees
boolean flag = false;  // Flag variable

// Initializing Water Sensor
int water_sensor = 8;  // Water sensor pin
int whiteled = 6;      // White LED pin

void setup() {
  // Ultrasonic Sensor Setup
  pinMode(redled, OUTPUT);   // Set red LED as output
  pinMode(trigPin, OUTPUT);  // Set trigger pin as output
  pinMode(echoPin, INPUT);   // Set echo pin as input

  // Servo Motor Setup
  Serial.begin(9600);        // Initialize serial communication
  servo.attach(servoPin);    // Attach servo to pin

  // Water Sensor Setup
  pinMode(water_sensor, INPUT);  // Set water sensor as input
  pinMode(whiteled, OUTPUT);     // Set white LED as output
}

void loop() {
  // Ultrasonic sensor distance measurement
  long duration, distance;
  
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure echo duration
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in centimeters
  distance = (duration / 2) / 29.1;

  // Check if object is within 10cm (leak detection)
  if (distance < 10) {
    digitalWrite(redled, HIGH);  // Turn on red LED
    servo.write(135);            // Move servo to 135 degrees
  } else {
    digitalWrite(redled, LOW);   // Turn off red LED
    servo.write(-135);           // Move servo to -135 degrees
  }

  // Check water sensor status
  if (digitalRead(water_sensor) == LOW) {
    digitalWrite(whiteled, HIGH);  // Turn on white LED if water detected
  } else {
    digitalWrite(whiteled, LOW);   // Turn off white LED if no water
  }
}
