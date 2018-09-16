//////////////////////////////////////
// M&M Sorter                       //
// By: Ethan Zohar and Benji Saltz  //
// Sorts M&M's by colour            //
//////////////////////////////////////

#include <Servo.h> // Includes the servo library

//Set all colour sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

//Initialize variables for colour sensor
int freqR = 0;
int freqG = 0;
int freqB = 0;

//Initialize variables for counting trials
int count = 0;
int count2 = 0;

//Initializes variables for detecting colours
boolean Red = false;
boolean Orange = false;
boolean Yellow = false;
boolean Green = false;
boolean Blue = false;
boolean Brown = false;
boolean White = false;

//Initializes variables for counting the amount of times a colour has been read
int redValue = 0;
int orangeValue = 0;
int yellowValue = 0;
int greenValue = 0;
int blueValue = 0;
int brownValue = 0;
int whiteValue = 0;

//Initializes booleans for starting and restarting the program
boolean start =  false;
boolean restart = true;

//Initializes variable for recieved message
char serialData;

Servo myservoTop;  // create servo object to control a servo
Servo myservoBottom;  // create servo object to control a servo

//Sets speed of motors
int timer = 25;

//Declares the angles for the motors to turn
int ColourSensorAngle = 110;
int DropAngle = 40;
int RedAngle = 172;
int OrangeAngle = 149;
int YellowAngle = 123;
int GreenAngle = 98;
int BlueAngle = 73;
int BrownAngle = 47;

//Initializes variables for counting number of coloured M&Ms
int redCount = 0;
int orangeCount = 0;
int yellowCount = 0;
int greenCount = 0;
int blueCount = 0;
int brownCount = 0;

//Value to keep track of what colour has been read
int colour = 100;

//Value to keep track of where the bottom servo is
int bottomAngle = 0;

//Variables to keep track of the colour sensor readings
boolean colourChosen = false;
boolean checkColour = false;

void setup() {
  //Sets pinmode
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  //Starts the serial monitor
  Serial.begin(9600);

  //Sets two of the colour sensor pins to the according position
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  myservoTop.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoBottom.attach(10); // attaches the servo on pin 10 to the servo object

  //Sets the servos to their starting position
  myservoTop.write(180);
  myservoBottom.write(180);
  delay(timer);
}

void loop() {
  if (start) { // If Python says the program should start
    if (restart) { // If the program needs to restart
      // Reset the servos' positions
      myservoTop.write(180);     
      myservoBottom.write(180);
      restart = false;
    }
    delay(1000);
    for (int i = 180; i >= ColourSensorAngle; i--) { // Moves the top servo to the colour sensor
      myservoTop.write(i);
      delay(timer);
    }

    // Resarts values for the colour sensor
    colourChosen = false;
    checkColour = false;

    while (checkColour == false) { // While no colour has ben chosen for the M&M
      //Reads the RGB values from the colour sensor
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      freqR = pulseIn(sensorOut, LOW);

      delay(50);

      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      freqG = pulseIn(sensorOut, LOW);

      delay(50);

      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      freqB = pulseIn(sensorOut, LOW);

      if (freqR >= 81 && freqR <= 84 && freqG >= 107 && freqG <= 111 && freqB >= 84 && freqB <= 87) { // Checks to see if the RGB value matches with the colour Red
        Red = true;
        count++;
      }
      if (freqR >= 73 && freqR <= 76 && freqG >= 103 && freqG <= 106 && freqB >= 84 && freqB <= 87) { // Checks to see if the RGB value matches with the colour Orange
        Orange = true;
        count++;
      }
      if (freqR >= 68 && freqR <= 72 && freqG >= 87 && freqG <= 91 && freqB >= 79 && freqB <= 83) { // Checks to see if the RGB value matches with the colour Yellow
        Yellow = true;
        count++;
      }
      if (freqR >= 81 && freqR <= 84 && freqG >= 96 && freqG <= 102 && freqB >= 80 && freqB <= 88) { // Checks to see if the RGB value matches with the colour Green
        Green = true;
        count++;
      }
      if (freqR >= 85 && freqR <= 88 && freqG >= 97 && freqG <= 100 && freqB >= 72 && freqB <= 75) { // Checks to see if the RGB value matches with the colour Blue
        Blue = true;
        count++;
      }
      if (freqR >= 85 && freqR <= 87 && freqG >= 106 && freqG <= 107 && freqB >= 84 && freqB <= 87) { // Checks to see if the RGB value matches with the colour Brown
        Brown = true;
        count++;
      }
      if (freqR >= 85 && freqR <= 87 && freqG >= 103 && freqG <= 106 && freqB >= 81 && freqB <= 83) { // Checks to see if the RGB value matches with the colour White
        White = true;
        count++;
      }

      if (count == 1) { // If only one colour has been matched
        if (Red) { // If that colour is Red
          redValue++;
        } 
        else if (Orange) { // If that colour is Orange
          orangeValue++;
        } 
        else if (Yellow) { // If that colour is Yellow
          yellowValue++;
        } 
        else if (Green) { // If that colour is Green
          greenValue++;
        } 
        else if (Blue) { // If that colour is Blue
          blueValue++;
        } 
        else if (Brown) { // If that colour is Brown
          brownValue++;
        } 
        else if (White) { // If that colour is White
          whiteValue++;
        }
      } 
      else {
        count2++; // Add 1 to a trial count
      }

      count = 0; // Reset the number of colours matched

      if (redValue >= 3) { // If the colour Red has been matched 3 or more times
        colour = 0;
        redCount++;
        colourChosen = true;
        checkColour = true;
      } 
      else if (orangeValue >= 3) { // If the colour Orange has been matched 3 or more times
        colour = 1;
        orangeCount++;
        colourChosen = true;
        checkColour = true;
      } 
      else if (yellowValue >= 3) { // If the colour Yellow has been matched 3 or more times
        colour = 2;
        yellowCount++;
        colourChosen = true;
        checkColour = true;
      } 
      else if (greenValue >= 3) { // If the colour Green has been matched 3 or more times
        colour = 3;
        greenCount++;
        colourChosen = true;
        checkColour = true;
      } 
      else if (blueValue >= 3) { // If the colour Blue has been matched 3 or more times
        colour = 4;
        blueCount++;
        colourChosen = true;
        checkColour = true;
      } 
      else if (brownValue >= 3) { // If the colour Brown has been matched 3 or more times
        colour = 5;
        brownCount++;
        colourChosen = true;
        checkColour = true;
      } 
      else if (whiteValue >= 3) { // If the colour White has been matched 3 or more times
        checkColour = true;
      }

      if (count2 > 50) { // If there have been more than 50 trials
        checkColour = true; // Break the loop
      }

      // Reset the colours read
      Red = false;
      Orange = false;
      Yellow = false;
      Green = false;
      Blue = false;
      Brown = false;
      White = false;
    }

    if (colourChosen) { // If a colour has been chosen
      // Reset the colour values
      redValue = 0;
      orangeValue = 0;
      yellowValue = 0;
      greenValue = 0;
      blueValue = 0;
      brownValue = 0;
      whiteValue = 0;
      count2 = 0;
      if (colour == 0) { // If the colour is Red
        for (int i = 180; i >= RedAngle; i--) { // Move the bottom servo to the RedAngle
          myservoBottom.write(i);
          delay(timer);
        }
        // Record the angle of the bottom servo
        bottomAngle = RedAngle;
      } 
      else if (colour == 1) { // If the colour is Orange
        for (int i = 180; i >= OrangeAngle; i--) { // Move the bottom servo to the OrangeAngle
          myservoBottom.write(i);
          delay(timer);
        }
        // Record the angle of the bottom servo
        bottomAngle = OrangeAngle;
      } 
      else if (colour == 2) { // If the colour is Yellow
        for (int i = 180; i >= YellowAngle; i--) { // Move the bottom servo to the YellowAngle
          myservoBottom.write(i);
          delay(timer);
        }
        // Record the angle of the bottom servo
        bottomAngle = YellowAngle;
      } 
      else if (colour == 3) { // If the colour is Green 
        for (int i = 180; i >= GreenAngle; i--) { // Move the bottom servo to the GreenAngle
          myservoBottom.write(i);
          delay(timer);
        }
        // Record the angle of the bottom servo
        bottomAngle = GreenAngle;
      } 
      else if (colour == 4) { // If the colour is Blue
        for (int i = 180; i >= BlueAngle; i--) { // Move the bottom servo to the BlueAngle
          myservoBottom.write(i);
          delay(timer);
        }
        // Record the angle of the bottom servo
        bottomAngle = BlueAngle;
      } 
      else if (colour == 5) { // If the colour is Brown
        for (int i = 180; i >= BrownAngle; i--) { // Move the bottom servo to the BrownAngle
          myservoBottom.write(i);
          delay(timer);
        }
        // Record the angle of the bottom servo
        bottomAngle = BrownAngle;
      }

      for (int i = ColourSensorAngle; i >= DropAngle; i--) { // Move the top servo to the DropAngle
        myservoTop.write(i);
        delay(timer);
      }

      delay(200);

      for (int i = bottomAngle; i <= 180; i++) { // Move the bottom servo back to the starting position
        myservoBottom.write(i);
        delay(timer);
      }

      for (int i = DropAngle; i <= 180; i++) { // Move the top servo back to the starting position
        myservoTop.write(i);
        delay(timer);
      }
    } else {
      // Send the final counts through the serial port
      Serial.print("-");
      Serial.print(redCount);
      Serial.print(" ");
      Serial.print(orangeCount);
      Serial.print(" ");
      Serial.print(yellowCount);
      Serial.print(" ");
      Serial.print(greenCount);
      Serial.print(" ");
      Serial.print(blueCount);
      Serial.print(" ");
      Serial.print(brownCount);
      Serial.println(" ");
      
      // Reset all values
      restart = true;
      start = false;
      count = 0;
      count2 = 0;
      redCount = 0;
      orangeCount = 0;
      yellowCount = 0;
      greenCount = 0;
      blueCount = 0;
      brownCount = 0;
    }
  } else {
    if (Serial.available() > 0) { // If you are waiting for a message
      serialData = Serial.read(); // Read the serial port
      if (serialData == '1') { // If the message is a 1
        start = true; // Start the program
      }
    }
  }
}




