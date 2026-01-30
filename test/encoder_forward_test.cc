#include <Arduino.h>

// motor pins
#define in1 A1
#define in2 A2
#define in3 A3
#define in4 A4

#define ena 6
#define enb 5

// encoder pins
#define rightc1 3   //swapping right pins to get positive for forward direction on connection
#define rightc2 11
#define leftc1 2
#define leftc2 10

void forward(int rightSpeed, int leftSpeed){
  rightSpeed = constrain(rightSpeed, -255, 255);
  leftSpeed = constrain(leftSpeed, -255, 255);
  if (rightSpeed >= 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    rightSpeed = -rightSpeed;
  }
  if (leftSpeed >= 0) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    leftSpeed = -leftSpeed;
  }
  analogWrite(ena, rightSpeed);
  analogWrite(enb, leftSpeed);
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(rightc1, INPUT);
  pinMode(rightc2, INPUT);  
  pinMode(leftc1, INPUT);
  pinMode(leftc2, INPUT);
  Serial.begin(9600);
}

void loop() {
  forward(200, 200);
}
