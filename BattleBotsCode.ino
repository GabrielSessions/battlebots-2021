
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
Adafruit_DCMotor *mySpinMotor = AFMS.getMotor(3);

//const int initSpeed = 100;
const int speedMax = 2000;
const int speedMin = -1200;

int zeroX = 1500;
int zeroY = 1463;
int yDiff = 400;
int xDiff = 400;

float maxPowerDist = sqrt(pow(xDiff,2) + pow(yDiff,2));

void setup() {
    Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

}

void loop() {
  int ydir = pulseIn(1, HIGH);
  int xdir = pulseIn(2, HIGH);
  int power = pulseIn(0, HIGH);
  
  if (ydir > zeroY-50 && ydir < zeroY+50 && xdir > zeroX-50 && xdir < zeroY+50){
     myMotor->setSpeed(0);
     myOtherMotor->setSpeed(0);
     int zeroX = xdir;
     int zeroY = ydir;
     
     
  }

  else if (ydir < zeroY-30){
    backward(xdir, ydir);
  }

  else if (ydir > zeroY+30){
    forward(xdir, ydir);
  }

  /*
  else if (xdir > zeroX-30 && xdir < zeroX+30 && ydir >= zeroY+30){
    forward(ydir);
  }
  else if (xdir > zeroX-30 && xdir < zeroX+30 && ydir <= zeroY-30){
    backward(ydir);
  }

  else if (xdir > zeroX+30){
    right (xdir, ydir);
  }

  else if (xdir < zeroX-30){
    left (xdir, ydir);
  }
  */



  if (power < 1050){
    spinner (power);
  }
  else{
    mySpinMotor->setSpeed(0);
  }
  
}

void forward(int x, int y){
  int xDist = abs(x - zeroX);
  int yDist = abs(y-zeroY);
  int total = xDist + yDist;
  float power = 255 * sqrt(pow(xDist, 2) + pow(yDist, 2)) / (yDiff*xDiff);
  float myMotorSpeed = 255*float(yDist)/yDiff;  
  float myOtherMotorSpeed = 255*float(yDist)/yDiff;  
  if (x - zeroX > xDiff){
    myMotorSpeed *= 0.4;
  }
  else if (x - zeroX < -1*xDiff){
    myOtherMotorSpeed *= 0.4;
  }
  myMotor->run(FORWARD);
  myOtherMotor->run(BACKWARD);
  myMotor->setSpeed(int(myMotorSpeed));
  myOtherMotor->setSpeed(int(myOtherMotorSpeed));

  
  
}



void left(int x, int y){

  myOtherMotor->run(BACKWARD);
  myOtherMotor->setSpeed(int(255*(x-zeroX)/xDiff));

  
  /*

  Serial.println("right");
  
  int xDist = x - zeroX;
  int yDist = abs(y-zeroY);
  float power = 255 * sqrt(pow(xDist, 2) + pow(yDist, 2)) / (yDiff*xDiff);
  float dist = power/255;
  
  if (y >= zeroY){
    //myMotor->run(FORWARD);
    myOtherMotor->run(BACKWARD);
    
  }

  else if (y < zeroY) {
    //myMotor->run(BACKWARD);
    myOtherMotor->run(FORWARD);
    
  }

  /*
  

  myMotor->setSpeed(int(power * (float(y)/zeroY)));
  myOtherMotor->setSpeed(int(power * float(x)/zeroX));

  /*
  Serial.println("left");
  
  int xDist = 1500-x;
  int yDist = abs(1463 - y);
  int dist = sqrt(pow(xDist, 2)+pow(yDist, 2));
  float power = sqrt(pow(x,2) + pow(y,2)) / maxPowerDist;
   if (y >= 1463){
    myMotor->run(FORWARD);
    myOtherMotor->run(BACKWARD);
    myMotor->setSpeed(power * abs(asin(yDist/dist)));
   myOtherMotor->setSpeed(power * abs(acos(xDist/dist)));
   }
   else{
    myMotor->run(BACKWARD);
    myOtherMotor->run(FORWARD);
    myMotor->setSpeed((int)(power * abs(asin(yDist/dist))));
   myOtherMotor->setSpeed((int)(power * abs(acos(xDist/dist))));
   }

   */
   
   
}


void right(int x, int y){
  /*
  Serial.println("right");
  
  int xDist = x - zeroX;
  int yDist = abs(y - zeroY);
  float power = 255 * sqrt(pow(xDist, 2) + pow(yDist, 2)) / (yDiff*xDiff);
  float dist = power/255;

  
  if (y >= zeroY){
    myMotor->run(FORWARD);
    myOtherMotor->run(BACKWARD);
    
  }

  else if (y < zeroY) {
    myMotor->run(BACKWARD);
    myOtherMotor->run(FORWARD);
  }

  
  myMotor->setSpeed(int(yDist/dist));
  myOtherMotor->setSpeed(int(xDist/dist));

    */

  myOtherMotor->run(FORWARD);
  myOtherMotor->setSpeed(int(255*(x-zeroX)/xDiff));
    
  
   
}

void backward(int x, int y){

  /*
  myMotor->run(BACKWARD);
  myOtherMotor->run(FORWARD);
  myMotor->setSpeed(255*(zeroY-y)/yDiff);
  myOtherMotor->setSpeed(255*(zeroY-y)/yDiff);

  */

  int xDist = abs(x - zeroX);
  int yDist = abs(y-zeroY);
  int total = xDist + yDist;
  float power = 255 * sqrt(pow(xDist, 2) + pow(yDist, 2)) / (yDiff*xDiff);
  float myMotorSpeed = 255*(y-zeroY)/yDiff;  
  float myOtherMotorSpeed = 255*(y-zeroY)/yDiff;  
  if (x - zeroX > xDiff){
    myMotorSpeed *= 1 - (float(xDist)/xDiff);
  }
  else if (x - zeroX < -1*xDiff){
    myOtherMotorSpeed *= 1 - (float(xDist)/xDiff);
  }
  myMotor->run(BACKWARD);
  myOtherMotor->run(FORWARD);
  myMotor->setSpeed(-1* int(myMotorSpeed));
  myOtherMotor->setSpeed(-1 *int(myOtherMotorSpeed));
}

void spinner (int spinSpeed){
  
  mySpinMotor->run(FORWARD);
  mySpinMotor->setSpeed(255);
  
  
  
}
