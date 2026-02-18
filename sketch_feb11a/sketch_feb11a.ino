//Pins for QTI connections on board (line sensors)
#define lineSensor1 47 
#define lineSensor2 49 
#define lineSensor3 51 


// RGB LED pins
#define redpin 45
#define greenpin 46
#define bluepin 44

// External RGB LED pins
#define externalRed 3
#define externalBlue 5
#define externalGreen 2

#include <Servo.h>
Servo servoLeft;   // Left wheel servo
Servo servoRight;  // Right wheel servo

int hashCounter = 0;  // Counts how many intersections we've crossed
int rfidLocation = 0; 
int i=0;


void setup() {
  Serial.begin(9600); //start the serial monitor so we can view the output
  Serial1.begin(9600); //Start the RFID monitor
  Serial2.begin(9600); // initialize Xbee Tx/Rx
  int state = 0;

  // Connect the servos to their pins
  servoLeft.attach(12);
  servoRight.attach(11);

  // Set up RGB LED pins as outputs
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  pinMode(externalRed, OUTPUT);
  pinMode(externalGreen, OUTPUT);
  pinMode(externalBlue, OUTPUT);
  
  // Turn LED off 
  analogWrite(redpin, 255);
  analogWrite(greenpin, 255);
  analogWrite(bluepin, 255);

  digitalWrite(externalRed, 0);
  digitalWrite(externalGreen, 0);
  digitalWrite(externalBlue, 0);

}

void loop() {
  // Read the three line sensors
  int qti1 = rcTime(lineSensor1); 
  int qti2 = rcTime(lineSensor2); 
  int qti3 = rcTime(lineSensor3); 

  // Calculate state as a 3-bit number representing which sensors see the line
  // state can be 0-7 depending on which sensors detect black/white
  int state = 4*light(qti1) + 2*light(qti2) + light(qti3);
  Serial.println(state);

  // Decide what to do based on sensor readings
  switch(state){
    case 0:  // All sensors on black 
      // Stop the robot
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);

      hashCounter++;  // We hit another intersection
      delay(500);
      // Flash different colors based on which intersection this is
       switch(hashCounter){
          case 1: 
            // Attempt to read from RFID
              if(Serial1.available() >0){
                  Serial.println("Reading: " + Serial1.read());
                  rfidLocation = hashCounter;
                  digitalWrite(externalGreen, 255);
                  delay(500);
                  digitalWrite(externalGreen,0);

                  while(Serial1.available() >0){
                  Serial1.read();
                }
              }
            else{
              digitalWrite(externalRed, 255);
              delay(500);
              digitalWrite(externalRed,0);
            }

            // purple
            analogWrite(redpin, 0);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 0);
            delay(1000);
            analogWrite(redpin, 255);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 255);
            break;
          case 2:
            // Attempt to read from RFID
            if(Serial1.available() >0){
                rfidLocation = hashCounter;
                digitalWrite(externalGreen, 255);
                delay(500);
                digitalWrite(externalGreen,0);

                while(Serial1.available() >0){
                  Serial1.read();
            }
            }
            else{
              digitalWrite(externalRed, 255);
              delay(500);
              digitalWrite(externalRed,0);
            }

            // green
            analogWrite(redpin, 255);
            analogWrite(greenpin, 0);
            analogWrite(bluepin, 255);
            delay(1000);
            analogWrite(redpin, 255);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 255);
            break;
          case 3:
            // Attempt to read from RFID
            if(Serial1.available() >0){
                rfidLocation = hashCounter;
                digitalWrite(externalGreen, 255);
                delay(500);
                digitalWrite(externalGreen,0);

                while(Serial1.available() >0){
                  Serial1.read();
            }
            }
            else{
              digitalWrite(externalRed, 255);
              delay(500);
              digitalWrite(externalRed,0);
            }

            // blue
            analogWrite(redpin, 255);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 0);
            delay(1000);
            analogWrite(redpin, 255);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 255);
            break;
          case 4:
            // Attempt to read from RFID
            if(Serial1.available() >0){
                rfidLocation = hashCounter;
                digitalWrite(externalGreen, 255);
                delay(500);
                digitalWrite(externalGreen,0);

                while(Serial1.available() >0){
                  Serial1.read();
            }
            }
            else{
              digitalWrite(externalRed, 255);
              delay(500);
              digitalWrite(externalRed,0);
            }

            // red
            analogWrite(redpin, 0);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 255);
            delay(1000);
            analogWrite(redpin, 255);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 255);
            break;
          case 5:
            // Attempt to read from RFID
            if(Serial1.available() >0){
                rfidLocation = hashCounter;
                digitalWrite(externalGreen, 255);
                delay(500);
                digitalWrite(externalGreen,0);

                while(Serial1.available() >0){
                  Serial1.read();
            }
            }
            else{
              digitalWrite(externalRed, 255);
              delay(500);
              digitalWrite(externalRed,0);
            }

            // white
            analogWrite(redpin, 0);
            analogWrite(greenpin, 0);
            analogWrite(bluepin, 0);
            delay(1000);
            analogWrite(redpin, 255);
            analogWrite(greenpin, 255);
            analogWrite(bluepin, 255);

            // Do a slight right turn until reaching the black line
            servoLeft.writeMicroseconds(1500);
            servoRight.writeMicroseconds(1700);
            delay(850);
            servoLeft.writeMicroseconds(1300);
            servoRight.writeMicroseconds(1600);
            break;
          case 6:  // Stop the robot completely after 6 intersections (the first one on the second track which is the RFID intersection)
            servoLeft.detach();
            servoRight.detach();
            
            if(Serial1.read() >1){
              switch(rfidLocation){
                case 1:
                  Serial2.print(')');
                  break;
                case 2:
                  Serial2.print('*');
                  break;
                case 3: 
                  Serial2.print('+');
                  break;
                case 4:
                  Serial2.print(',');
                  break;
                case 5:
                  Serial2.print('-');
                  break;
              }
              digitalWrite(externalGreen, 255);
              delay(500);
              digitalWrite(externalGreen,0);
              while(i < 10){
                digitalWrite(externalBlue,255);
                delay(250);
                digitalWrite(externalBlue,0);
                delay(250);
                i++;
              }
              
            }
            else{
              Serial2.print('(');
              digitalWrite(externalRed, 255);
              delay(500);
              digitalWrite(externalRed,0);
            }
            break;
        }

      // After flashing LED, move forward a bit to get past the intersection
      delay(1000);
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1600);
      delay(300);

      break;

    case 1:  // Right sensor on black - veer left
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1500);
      break;
    case 2:  // Unlikely
      break;
    case 3:  // Middle and right on black - veer left
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1500);
      break;
    case 4:  // Left sensor on black - veer right
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1700);
      break;
    case 5:  // Left and right on black - go straight
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1600);
      break;
    case 6:  // Left and middle on black - veer right
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1700);
      break;
    case 7:  // All sensors on white - do nothing (off the line)
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

// Converts sensor reading to binary: 1 if on black line, 0 if on white
int light(long rcTime){
  if(rcTime < 150){  // Lower reading = darker surface (black line)
    return 1;
  }
  else{  // Higher reading = lighter surface (white background)
    return 0;
  }
}