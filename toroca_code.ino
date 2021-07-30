//The following three lines of code includes libraries that will aid us use Adafruit motorShield
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Selecting ports M1, M2, M3 and M4. 
Adafruit_DCMotor *motorLB = AFMS.getMotor(1);
Adafruit_DCMotor *motorLF = AFMS.getMotor(2);
Adafruit_DCMotor *motorRB = AFMS.getMotor(4);
Adafruit_DCMotor *motorRF = AFMS.getMotor(3);

//setting pins for input buttons
int xButton=12;
int yButton=11;
int resetButton=10;
int actuateButton=9;


//To prevent creating many string variables, this variable will be assigned to any value to be printed
String toPrint="";

//initial (x,y) coordinates set to (0,0)
int x=0;
int y=0;

/*runs only once on startup*/
void setup() {
  //setting buttons as inputs
  pinMode(xButton, INPUT);
  pinMode(yButton, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(actuateButton, INPUT);
  // Starting serial communication
  Serial.begin(9600); 
  //printing welcoming message
  Serial.println("Welcome, I am cord-E ---> Ready for corrdinates");
  //beginning motorShield object
  AFMS.begin();
  //setting motor speed to 48 rpm so it covers 0.5m in 3s. This will be used to move forward and move back
  setMotorSpeed(48);
  //turns right in the beginning to face the x direction
  turnRight();
}

/*runs forever */
void loop() {
  //checks if the reset button is pressed
  if(digitalRead(resetButton)==1){
    x=0;
    y=0;
    Serial.println("Reset button pressed, cordinates---> (0,0)");
    delay(300);
  }
  //checks if the actuate button is pressed
  if(digitalRead(actuateButton)==1){
    actuate(x,y);
    toPrint="Current location---> (";
    toPrint=toPrint+x;
    toPrint=toPrint +",";
    toPrint=toPrint+y;
    toPrint=toPrint+")";
    Serial.println(toPrint);
    delay(300);
  }
  //checks if the x button is pressed
  if(digitalRead(xButton)==1){
    x++;
    toPrint="x value set to: ";
    toPrint=toPrint+x;
    Serial.println(toPrint);
    delay(300);
  }
  //checks if the y button is pressed
  if(digitalRead(yButton)==1){
    y++;
    toPrint="y value set to: ";
    toPrint=toPrint+y;
    Serial.println(toPrint);
    delay(300);
  }
}

/*sets motor speed (for the tyres) */
void setMotorSpeed(int speeeed){
  motorLB->setSpeed(speeeed);
  motorLF->setSpeed(speeeed);
  motorRB->setSpeed(speeeed);
  motorRF->setSpeed(speeeed);
}

/*moves robot forward */
void moveForward(){
  setMotorSpeed(48);
  motorLB->run(FORWARD);
  motorLF->run(FORWARD);
  motorRF->run(FORWARD);
  motorRB->run(FORWARD);
  delay(3000);
}

/*moves robot backward */
void moveBack(){
  setMotorSpeed(48);
  motorLB->run(BACKWARD);
  motorLF->run(BACKWARD);
  motorRF->run(BACKWARD);
  motorRB->run(BACKWARD);
  delay(3000);
}

/*turns robot right */
void turnRight(){
  setMotorSpeed(400);
  motorLB->run(BACKWARD);
  motorLF->run(BACKWARD);
  motorRF->run(FORWARD);
  motorRB->run(FORWARD);
 delay(1000);
}

/*turns robot left */
void turnLeft(){
 setMotorSpeed(180);
 motorLB->run(FORWARD);
 motorLF->run(FORWARD);
 motorRF->run(BACKWARD);
 motorRB->run(BACKWARD);
 delay(1000);
}

/*Halts the robot*/
void stopMoving(){
  motorLB->run(RELEASE);
  motorLF->run(RELEASE);
  motorRF->run(RELEASE);
  motorRB->run(RELEASE);
  delay(100);
}

/*Sets robot in motion to coordinates (x,y)*/
void actuate(int x, int y){
  Serial.println("Actuate button pressed ---> moving...");
  for(int i=0;i<x;i++){
    moveForward();
  }
  turnLeft();
  for(int i=0;i<y;i++){
    moveForward();
  }
  stopMoving();
  Serial.println("Done moving");
}

/* by ToRoCa*/
