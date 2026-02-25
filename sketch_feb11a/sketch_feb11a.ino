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

#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> 
#include <SoftwareSerial.h>
#define TxPin 14
#define num 17
SoftwareSerial mySerial = SoftwareSerial (255, TxPin);


#include <Servo.h>
Servo servoLeft;   // Left wheel servo
Servo servoRight;  // Right wheel servo

int hashCounter = 0;  // Counts how many intersections we've crossed
int rfidLocation = 0; // Stores which intersection the RFID tag was detected at
int i=0;              // Loop counter used for the blue LED blink at the end
int scores[5];
char score;
char lastIncoming;

void setup() {
  Serial.begin(9600); //start the serial monitor so we can view the output
  Serial1.begin(9600); //Start the RFID monitor
  Serial2.begin(9600); // initialize Xbee Tx/Rx
  int state = 0;


  mySerial.begin(9600);
  delay(100);
  mySerial.write(12); // clear
  mySerial.write(22); // no cursor no blink
  mySerial.write(17); // backlight
  delay(10);
  Wire.begin(); //Joing I2C bus
  

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

  // Turn external LED off too
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

    if(Serial2.available()) { // Is XBee data available?
    char incoming = Serial2.read(); // Read character
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
            
    int groupNo;
        if(incoming!=lastIncoming){
          groupNo = incoming/10;
          scores[groupNo - 4] = incoming % 10;
          lastIncoming = incoming;
        }
    }

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
            
            // If there's a valid RFID read here, send the location over XBee and light up green
            if(Serial1.read() >1){
              // Send a unique character over XBee to indicate which intersection the tag was found at. Correspond to ASCII values with 40 - 45  (4 indicating group number, second digit indicating which intersection the tag was found at, if 0, there's no tag at the final intersection)
              switch(rfidLocation){
                case 1:
                score = ')';
                  Serial2.print(score);
                  break;
                case 2:
                score = '*';
                  Serial2.print(score);
                  break;
                case 3: 
                score = '+';
                  Serial2.print(score);
                  break;
                case 4:
                  score = ',';
                  Serial2.print(score);
                  break;
                case 5:
                score = '-';
                  Serial2.print(score);
                  break;
              }
              // Flash green once to confirm we sent the location
              digitalWrite(externalGreen, 255);
              delay(500);
              digitalWrite(externalGreen,0);

              // Blink blue 10 times to signal we're done
              while(i < 10){
                digitalWrite(externalBlue,255);
                delay(250);
                digitalWrite(externalBlue,0);
                delay(250);
                i++;
              }
              
            }
            else{
              score = '(';
              Serial2.print(score);
              digitalWrite(externalRed, 255);
              delay(500);
              digitalWrite(externalRed,0);
            }

            scores[0] = score % 10;

            String myString = "";
            for(int m = 0; m<5;m++){
              myString+= String(scores[m]);
              if(m<5-1){
                myString+= "-";
                }
              }
            mySerial.print(myString);
            
            break;
        }

      // Wait a moment, then nudge forward to clear the intersection so we don't re-trigger case 0
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