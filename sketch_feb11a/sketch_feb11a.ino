//Pins for QTI connections on board
#define lineSensor1 47 
#define lineSensor2 49 
#define lineSensor3 51 

#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  Serial.begin(9600); //start the serial monitor so we can view the output
  int state = 0;

  servoLeft.attach(12);
  servoRight.attach(11);
}

void loop() {
  int qti1 = rcTime(lineSensor1); 
  int qti2 = rcTime(lineSensor2); 
  int qti3 = rcTime(lineSensor3); 

  int state = 4*light(qti1) + 2*light(qti2) + light(qti3);
  Serial.println(state);


  switch(state){
    case 0:
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
      delay(1000);
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1600);
      delay(300);
      break;

    case 1:
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1500);
      break;
    case 2:
      break;
    case 3: 
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1500);
      break;
    case 4:
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1700);
      break;
    case 5:
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1600);
      break;
    case 6: 
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1700);
      break;
    case 7: 
      break;
  }
}

//Defines funtion 'rcTime' to read value from QTI sensor
// From Ch. 6 Activity 2 of Robotics with the BOE Shield for Arduino
long rcTime(int pin){
  pinMode(pin, OUTPUT);    // Sets pin as OUTPUT
  digitalWrite(pin, HIGH); // Pin HIGH
  delay(1);                // Waits for 1 millisecond
  pinMode(pin, INPUT);     // Sets pin as INPUT
  digitalWrite(pin, LOW);  // Pin LOW
  long time = micros();    // Tracks starting time
  while(digitalRead(pin)); // Loops while voltage is high
  time = micros() - time;  // Calculate decay time
  return time;             // Return decay time
}

int light(long rcTime){
  if(rcTime < 150){
    return 1;
  }
  else{
    return 0;
  }
}