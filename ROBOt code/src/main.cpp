#include "Arduino.h"

#include <Servo.h>  //import  servo library

#include <AFMotor.h>
#include <dht.h>

dht DHT;

#define DHT11_PIN A5



AF_DCMotor motor_left(1,MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor_right(2, MOTOR12_64KHZ);

const int speed = 75; // percent of maximum speed
const int LED = 12;
int pwm;
Servo myServo;
char dataa = 0;



void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void moveStop();
void right_car();
void left_car();
void temp();

//--------------------------------------------------------------------------------------------------------------------------

void setup()
{
  //BTserial.begin(9600);
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(12, OUTPUT);        //Sets digital pin 13 as output pin
  pwm= map(speed, 0,100, 0,255);
  motor_left.setSpeed(pwm); //set the speed of the motors, between 0-255
  motor_right.setSpeed (pwm);
  digitalWrite(LED, LOW);
  myServo.attach(10);
  myServo.write(90);
}

//-----------------------------------------------------------------------------------------------------------------------------

void loop() {
  temp();

  if(Serial.available()>0) //send data only when you receive data:
  {
    dataa = Serial.read(); //Read the incoming data and store it into variable data
    Serial.print(dataa); //print value inside data in serial monitor
    Serial.print("\n"); //New line
    if(dataa == 'f'){
      moveForward();
      digitalWrite(LED, LOW);
    }
    else if (dataa == 'b') {
      moveBackward();
      digitalWrite(LED, LOW);
    }
    else if (dataa == 's') {
      moveStop();
      digitalWrite(LED, LOW);
    }
    else if (dataa == 'l') {
      turnLeft();
      digitalWrite(LED, LOW);
    }
    else if (dataa == 't') {
      turnRight();
      digitalWrite(LED, LOW);
    }
    else if (dataa == '1') {
      digitalWrite(LED, HIGH);
    }
    else if (dataa == '0') {
      digitalWrite(LED, LOW);
    }
    else if (dataa == 'z') {
      myServo.write(180);
    }
    else if (dataa == '4') {
      myServo.write(135);
    }
    else if (dataa == '9') {
      myServo.write(90);
    }
    else if (dataa == '3') {
      myServo.write(45);
    }
    else if (dataa == '8') {
      myServo.write(0);
    }



  }


}
//----------------------------------------------------------------------------
void temp()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.print(DHT.humidity);
  Serial.print(";\n");
  delay(500);

}

//-----------------------------------------------------------------------------------------------------------------------------

void moveForward(){
  motor_left.run(FORWARD);
  motor_right.run(FORWARD);
}

//-----------------------------------------------------------------------------------------------------------------------------

void moveBackward(){
  motor_left.run(BACKWARD);
  motor_right.run(BACKWARD);
}


//-----------------------------------------------------------------------------------------------------------------------------

void moveStop(){
  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
}


//-----------------------------------------------------------------------------------------------------------------------------

void turnRight() {
  motor_left.run(FORWARD);      // turn motor 1 forward
  motor_right.run(BACKWARD);     // turn motor 2 backward
  //delay(400); // run motors this way for 400ms
  //motor_left.run(FORWARD);      // set both motors back to forward
  //motor_right.run(FORWARD);
}

//-----------------------------------------------------------------------------------------------------------------------------

void turnLeft() {
  motor_left.run(BACKWARD);      // turn motor 1 forward
  motor_right.run(FORWARD);     // turn motor 2 backward
  //delay(400); // run motors this way for 400ms
  //motor_left.run(FORWARD);      // set both motors back to forward
  //motor_right.run(FORWARD);
}

//-------------------------------------------------------------------------------------------------------------------
void right_car()
{
  myServo.write(0);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor_left.run(FORWARD);      // turn motor 1 forward
  motor_right.run(BACKWARD);     // turn motor 2 backward
  delay(1000);
  moveStop();
}
//-----------------------------------------------------------------------------------------------------------------------------
