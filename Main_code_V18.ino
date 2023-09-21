//infrared sensor setup
#include <QTRSensors.h>              //Include library to control the QTRRC reflectance sensor
QTRSensors qtr;                      //set up reflectance sensor instance
const uint8_t SensorCount = 8;       // declare number of IRsensors
uint16_t sensorValues[SensorCount];  //declare array to hold sensor values

//ultrasonic sensor setup
#include <NewPing.h>  // Include Library for the ultrasonic Sensor
// Define pins for ultrasonic sensor
#define trigPin 12                             //set pin for ultrasonic sensor trigger
#define echoPin 12                             //set pin for ultrasonic sensor echo
int maxdistance = 20;                          // set maximum distance the ultrasonic sensor can read to 20cm
NewPing sonar(trigPin, echoPin, maxdistance);  // Create NewPing object with maximum distance of 20cm

//continious motor setup
#include <Servo.h>  //Include library to contol the 2 continious servo motors
Servo myservo1;     //Setup first servo instance
Servo myservo2;     //Setup second servo instance
int motor1 = 11;    // define pin for left wheel
int motor2 = 10;    // define pin for right wheel

//lcd display setup
#include <SoftwareSerial.h>
SoftwareSerial lcd = SoftwareSerial(255, A2);

//general variables

int movecount;        // declare variable to control PWM of motors
int position;         // declare variable to hold the position of black line
int maininter = 0;    // delare variable to count main intersections
int searchinter = 0;  //Vairable to count all intersections
int distanceA = 0;    // declare variable to determine how far an obstacle is for all parking spots on the right
int distanceB = 0;    // declare variable to determine how far an obstacle is for all parking spots on the left
int obs1a = 0;        // variable to hold parking spot 1 on the right availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int obs1b = 0;        // variable to hold parking spot 1 on the left availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int obs2a = 0;        // variable to hold parking spot 2 on the right availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int obs2b = 0;        // variable to hold parking spot 2 on the left availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int obs3a = 0;        // variable to hold parking spot 3 on the right availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int obs3b = 0;        // variable to hold parking spot 3 on the left availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int obs4a = 0;        // variable to hold parking spot 4 on the right availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int obs4b = 0;        // variable to hold parking spot 4 on the left availability (0 - not checked, 1- checked & obstacle present, 2- checked & no obstacle)
int rightpark = 0;    // variable to control parking on the right
int leftpark = 0;     // variable to control parking on the left
int i = 0;            // varible for the for loop counter in the first odd intersection
int j = 0;            // varible for the for loop counter in the second odd intersection
int k = 0;            // varible for the for loop counter in the third odd intersection
int l = 0;            // varible for the for loop counter in the forth odd intersection
int totalobstacle;    // variable to count total number of obstacles seen before parking


void setup() {
  // put your setup code here, to run once:
  //Reflectance Sensor Setup
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 2, 3, 4, 5, 6, 7, 8, 9 }, SensorCount);  //determine arduino pins for the reflectance sensor

  pinMode(A0, OUTPUT);     //set Red LED to output
  pinMode(A1, OUTPUT);     // set blue LED to output
  pinMode(A2, OUTPUT);     // set LCD to output
  digitalWrite(A2, HIGH);  // make the LCD pin high
  lcd.begin(9600);         // start serial communication with lcd
  lcd.write(12);           // clear lcd
  lcd.write(17);           // turn on back light
  Serial.begin(9600);      // begin serial monitoring with computer

  //attach servo motors
  myservo1.attach(motor1);  // attached left servo
  myservo2.attach(motor2);  // attach right servo


  //Calibration Sequence
  // spin left and callibrate sensor
  for (int i = 0; i < 15; i++) {
    movecount = 1;
    qtr.calibrate();
    spinleft();
    delay(20);
  }
  // spin right and callibrate sensor
  for (int i = 0; i < 30; i++) {
    movecount = 1;
    qtr.calibrate();
    spinright();
    delay(20);
  }
  //spinleft and callibrate sensors

  for (int i = 0; i < 15; i++) {
    movecount = 1;
    qtr.calibrate();
    spinleft();
    delay(20);
  }
  // turn left
  movecount = 10;
  turnleft();
}

void loop() {
  // put your main code here, to run repeatedly:
  position = qtr.readLineBlack(sensorValues);  // read position value

  // run this block of code whenever we are on the track and not at an intersection. i.e whenever the first and last sensor are not on the black line
  if ((sensorValues[0] < 500) && (sensorValues[7] < 500)) {
    do {
      //behaviour at each mainintersection (i.e odd intersection on the map)
      switch (maininter) {
        case 0:  // when main intersection is zero, simply line follow
          linefollow(); //perform corrective measures to ensure robot is centered on black line
          break;

        case 1:
          if (searchinter == 1) {

            distanceA += sonar.ping_cm(); // check if there is an obstacle
            linefollow(); //perform corrective measures to ensure robot is centered on black line

            if (distanceA > 0) { // if there is an obstacle in the first parking lot, make obs1a 1
              obstacleindication();// indicate an obstacle
              obs1a = 1; 


            } else if (distanceA == 0) {// if there is an obstacle in the first parking lot, make obs1a 2

              obs1a = 2;

            } else {
              linefollow(); //perform corrective measures to ensure robot is centered on black line
            }
          } else if (searchinter == 4) {

            distanceB += sonar.ping_cm();
            linefollow(); //perform corrective measures to ensure robot is centered on black line



            if (distanceB > 0) { // if there is an obstacle in the first parking lot, make obs1b 1
              obstacleindication(); // indicate obstacle
              obs1b = 1;

            } else if (distanceB == 0) { // if there is an obstacle in the first parking lot, make obs1b 2
              obs1b = 2;

            } else {

              linefollow(); //perform corrective measures to ensure robot is centered on black line
            }

          } else {

            linefollow(); //perform corrective measures to ensure robot is centered on black line
          }
          break;

        case 2:
          linefollow(); //perform corrective measures to ensure robot is centered on black line
          distanceA = 0;  // take distance readings to zero
          distanceB = 0;  // take distance readings to zero
          break;
        // perform similar sequence as case 1
        case 3:
          if (searchinter == 7) {

            distanceA += sonar.ping_cm();
            linefollow();


            if (distanceA > 0) {
              obstacleindication();
              obs2a = 1;

            } else if (distanceA == 0) {
              obs2a = 2;

            } else {
              linefollow();
            }
          } else if (searchinter == 10) {


            distanceB += sonar.ping_cm();
            linefollow();

            if (distanceB > 0) {
              obstacleindication();
              obs2b = 1;

            } else if (distanceB == 0) {
              obs2b = 2;

            } else {

              linefollow();
            }

          } else {

            linefollow();
          }
          break;
        // perform similar sequence as case 2
        case 4:
          linefollow();
          distanceA = 0;
          distanceB = 0;
          break;
        //perform similar sequence as case 1
        case 5:
          if (searchinter == 13) {

            distanceA += sonar.ping_cm();
            linefollow();


            if (distanceA > 0) {
              obstacleindication();
              obs3a = 1;

            } else if (distanceA == 0) {
              obs3a = 2;

            } else {
              linefollow();
            }
          } else if (searchinter == 16) {


            distanceB += sonar.ping_cm();
            linefollow();


            if (distanceB > 0) {
              obstacleindication();
              obs3b = 1;

            } else if (distanceB == 0) {
              obs3b = 2;

            } else {

              linefollow();
            }

          } else {

            linefollow();
          }
          break;
        // perform similar sequence as case 3
        case 6:
          linefollow();
          distanceA = 0;
          distanceB = 0;
          break;
        // perform similar sequence as case 1
        case 7:
          if (searchinter == 19) {

            distanceA += sonar.ping_cm();
            linefollow();

            if (distanceA > 0) {
              obstacleindication();
              obs4a = 1;

            } else if (distanceA == 0) {
              obs4a = 2;

            } else {
              linefollow();
            }
          } else if (searchinter == 22) {


            distanceB += sonar.ping_cm();
            linefollow();


            if (distanceB > 0) {
              obstacleindication();
              obs4b = 1;

            } else if (distanceB == 0) {
              obs4b = 2;

            } else {

              linefollow();
            }

          } else {

            linefollow();
          }
          break;
      }
    } while ((sensorValues[0] < 500) && (sensorValues[1] < 500) && (sensorValues[6] < 500) && (sensorValues[7] < 500));
  }

//code sequence at every main intersection
  else if (((sensorValues[0] > 900) && (sensorValues[1] > 900) && (sensorValues[2] > 900) && (sensorValues[5] > 900) && (sensorValues[6] > 900) && (sensorValues[7] > 900)) && (maininter == 0 || (maininter == 2 && searchinter == 6) || (maininter == 4 && searchinter == 12) || (maininter == 6 && searchinter == 18))) {
    intersectionindication(); // indicate the presence of an intersection
    mainintersection(); // perform main intersection sequence

  }
//code sequence at other intersections that are not the main intersection
  else if ((sensorValues[0] > 900) && (sensorValues[1] > 900) && (sensorValues[2] > 900) && (sensorValues[5] > 900) && (sensorValues[6] > 900) && (sensorValues[7] > 900)) {
    if ((searchinter == 1 && obs1a == 1) || searchinter == 3 || (searchinter == 7 && obs2a == 1) || searchinter == 9 || (searchinter == 13 && obs3a == 1) || searchinter == 15 || (searchinter == 19 && obs4a == 1) || searchinter == 21) {
      movecount = 20;
      intersectionindication(); // indicate the presence of an intersection
      spinright(); // spin right

      delay(900); // delay to ensure a 180 turn
      searchinter += 1; // add 1 to the all intersection counter
    // here we say if an obstacle is present, move on to the next spot
    } else if ((searchinter == 4 && obs1b == 1) || (searchinter == 10 && obs2b == 1) || (searchinter == 16 && obs3b == 1) || (searchinter == 22 && obs4b == 1)) {
      movecount = 20;
      intersectionindication(); //indicate the presence of an intersection
      turnleft(); // turn left
      delay(700); // delay to ensure 90 degrees turn
      stopmotors(); // stop motors
      delay(5); // delay 
      searchinter += 1; // add 1 to the all intersection counter
      maininter += 1;
    // here if an obstacle is not present on any of the right lots we go park  
    } else if ((searchinter == 1 && obs1a == 2) || (searchinter == 7 && obs2a == 2) || (searchinter == 13 && obs3a == 2) || (searchinter == 19 && obs4a == 2)) {
      intersectionindication();
      parkright();
// here if an obstacle is not present of any of the left lots we go park
    } else if (searchinter == 4 && obs1b == 2 || (searchinter == 10 && obs2b == 2) || (searchinter == 16 && obs3b == 2) || (searchinter == 22 && obs4b == 2)) {
      intersectionindication();
      parkleft();
// at other intersections that are not key intersections, we move forward and add 1 to all intersection counter
    } else {
      movecount = 20;
      intersectionindication(); // indicate intersection
      forward();
      searchinter += 1;

      delay(50);
    }
    position = qtr.readLineBlack(sensorValues);
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Function Code Section

// led code to indicate parking. turn both blue and red leds on and off
void parkingindication() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  delay(500);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  delay(500);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  delay(500);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
}

// led code to turn red led on and off
void obstacleindication() {
  digitalWrite(A0, HIGH);
  delay(50);
  digitalWrite(A0, LOW);
}

// led code to turn blue led on
void intersectionindication() {
  digitalWrite(A1, HIGH);
  delay(50);
  digitalWrite(A1, LOW);
}

// main intersection code that turn the robot right and adds 1 to both main intersection counter and all intersection counter
void mainintersection() {
  position = qtr.readLineBlack(sensorValues);
  movecount = 20;
  turnright();
  delay(700);
  maininter += 1;
  searchinter += 1;
}

// code sequence to park right
void parkleft() {
  if (leftpark == 0) {
    lcd.print("Parking.........."); // indicate parking on the LCD
    movecount = 20;
    turnleft(); // turn left 90 degrees
    delay(700);
    leftpark += 1; // add one to left intersection counter
  } else if (leftpark == 1) {
    movecount = 20;
    turnleft(); // turn left 90 degrees again
    delay(700);
    leftpark += 1; // add one to left intersection counter
  } else {
    stopmotors(); // stop motors at T zone
    delay(5000);
    lcd.write(12); // clear lcd
    totalobstacle = obs1a + obs1b + obs2a + obs2b + obs3a + obs3b + obs4a + obs4b - 2; // sum up all obstacle reading and subtract 2 because a free spot will have an obstacle counter of 2
    lcd.print("Total Obstacles =");  
    lcd.print(totalobstacle); // display total number of obstacles on lcd
    parkingindication(); // indicate parking lights
    delay(7000);
  }
}

// code sequence to park right, similar to parking left. We turn right here.
void parkright() {
  if (rightpark == 0) {
    lcd.print("Parking..........");
    movecount = 20;
    spinright();
    delay(1000);
    rightpark += 1;
  } else if (rightpark == 1) {
    movecount = 20;
    turnright();
    delay(700);
    rightpark += 1;
  } else if (rightpark == 2) {
    movecount = 20;
    turnright();
    delay(700);
    rightpark += 1;
  } else {
    stopmotors();
    delay(5000);
    totalobstacle = obs1a + obs1b + obs2a + obs2b + obs3a + obs3b + obs4a + obs4b - 2;
    lcd.write(12);
    lcd.print("Total Obstacles =");
    lcd.print(totalobstacle);
    parkingindication();
    delay(7000);
  }
}

// line follow code
void linefollow() {
  position = qtr.readLineBlack(sensorValues);
  // ensure the postion of the black line is between 3200 and 3800. a well centered blackline will be at 3500
  if (position < 3200) { 
    do {
      movecount = 1;
      turnright();
      position = qtr.readLineBlack(sensorValues);
    } while (position < 3200);
  } else if (position > 3800)
    do {
      movecount = 1;
      turnleft();
      position = qtr.readLineBlack(sensorValues);
    } while (position > 3800);
  movecount = 5;
  forward();
  position = qtr.readLineBlack(sensorValues);
}
// code to move robot forward
void forward() {
  for (int i = 0; i < movecount; i++) {
    myservo1.write(170);
    myservo2.write(10);
    delay(5);
  }
}

// code to stop motors
void stopmotors() {
  for (int i = 0; i < movecount; i++) {
    myservo1.write(90);
    myservo2.write(90);
    delay(20);
  }
}

// code to turn right with one wheel on
void turnright() {
  for (int i = 0; i < movecount; i++) {
    myservo1.write(170);
    myservo2.write(90);
    delay(15);
  }
}
// code to turn left with one wheel on
void turnleft() {
  for (int i = 0; i < movecount; i++) {
    myservo1.write(90);
    myservo2.write(10);
    delay(15);
  }
}

//code to turn right with both wheels on
void spinright() {
  for (int i = 0; i < movecount; i++) {
    myservo1.write(170);
    myservo2.write(170);
    delay(10);
  }
}
//code to turn left with both wheels on
void spinleft() {
  for (int i = 0; i < movecount; i++) {
    myservo1.write(10);
    myservo2.write(10);
    delay(10);
  }
}
