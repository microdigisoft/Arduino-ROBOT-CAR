#include <NewPing.h>
#include <Servo.h>  //servo library
#include <AFMotor.h>
#define echoPin A0        // attach Echo of HC-SR04 pin to Analog pin 
#define trigPin A1        // attach trig of HC-SR04 pin to Analog pin 
#define MAX_DISTANCE 450
#define MAX_SPEED 100 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(4, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(2, MOTOR34_1KHZ);
NewPing sonar(trigPin,  echoPin, MAX_DISTANCE);
Servo myservo;      // create servo object to control servo
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int rightDistance = 0, leftDistance = 0;
void Stop();
int Distance_test();  void forward(); void back(); void left() ; void right();
boolean goesForward = false;
int speedSet = 0;
int distanceR = 0;
int distanceL =  0;
void setup() {
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  myservo.attach(10);  // attach servo on pin 3 to servo object
  Stop();// Stop all the motors

}
void loop() {
  Serial.print("Normal_Distance: ");
  Serial.print(distance);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  delay(100);

  if (distance <= 50)
  {
    Stop();//Stop all the motors
    delay(100);
    back();// Move backword
    delay(300);
    Stop();//Stop all the motors
    delay(250);
    lookRight();// look for obstruction in right side
    distanceR = distanceRight();// Read distace for right side
    delay(250);
    lookLeft();// look for obstruction in left side
    distanceL = distanceLeft();// Read distace for left side
    delay(250);

    if (distanceR > distanceL)// Compare the distace for left and right positon
    {
      Stop();//Stop all the motors
      left();// Move robot to left
      delay(250);
    } else if (distanceR < distanceL)//// Compare the distace for left and right positon
    {
      Stop();//Stop all the motors
      right();// Move robot to left

      delay(250);
    }
  } else
  {
    forward();// Move robot forward
  }
  distance = distance;// read distance 
}
// Below function is to read the data for Right side obstruction for ultrasonic sensor
int distanceRight() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distanceR = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Right_Distance: ");
  Serial.print(distanceR);
  Serial.println(" cm");
  return distanceR;
}
// Below function is to read the data for Left side obstruction for ultrasonic sensor
int distanceLeft() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distanceL = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Left_Distance: ");
  Serial.print(distanceL);
  Serial.println(" cm");
  return distanceL;
}
int lookRight()// Function to check for the right side distance using servo motor movement
{
  myservo.write(50);
  delay(500);
  //int distance = distance;
  delay(100);
  myservo.write(115);
  // return distance;
}

int lookLeft()// Function to check for the left side distance using servo motor movement
{
  myservo.write(170);
  delay(500);
  // int distance = distance;
  delay(100);
  myservo.write(115);
  //return distance;
  delay(100);
}
//Below function to stop all 4 motors
void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  Serial.println("Stop");
}

//Ultrasonic distance measurement method
int Distance_test() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  float Fdistance = pulseIn(echoPin, HIGH);
  Fdistance = Fdistance / 58;
  return (int)Fdistance;
}
// Function to move robot forward
void forward() {

  if (!goesForward)
  {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.setSpeed(60);
    motor2.setSpeed(60);
    motor3.setSpeed(60);
    motor4.setSpeed(60);
    delay(5);
    Serial.println("Forward");
  }
}
// Function to move robot reverse
void back() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(60);
  motor2.setSpeed(60);
  motor3.setSpeed(60);
  motor4.setSpeed(60);
  delay(5);
  Serial.println("Back");
}
// Function to move robot left
void left() {
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  motor3.setSpeed(80);
  motor4.setSpeed(80);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  Serial.println("Left");
  delay(200);
}
// Function to move robot right
void right() {
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  motor3.setSpeed(80);
  motor4.setSpeed(80);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  Serial.println("Right");
  delay(200);
}
// Function to read distace using ultrasonic sensor
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 450;
  }
  return cm;
}
