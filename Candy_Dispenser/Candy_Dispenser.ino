#include <Servo.h>
#include <LiquidCrystal.h>
#include <NewPing.h>

Servo myServo1;
Servo myServo2;
Servo myServo3;
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  myServo1.attach(7);
  // myServo2.attach(8);
  // myServo3.attach(9);
  
  myServo1.write(0);
  // myServo2.write(0);
  // myServo3.write(0);

  lcd.begin(16, 2);
}

void loop() {

  /**
   for (int i = 0; i <= 180; i++)
  {
    myServo1.write(i); //write the i angle to the servo
    delay(15); //delay 15ms
  }
  for (int i = 180; i >= 0; i--)
  {
    myServo1.write(i); //write the i angle to the servo
    delay(15); //delay 15ms
  }
  */

  delay(100);
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  int distance = uS / US_ROUNDTRIP_CM;
  lcd.setCursor(0, 0);//Place the cursor at Line 1, Column 1. From here the characters are to be displayed
  lcd.print("Distance:");////Print Distance: on the LCD
  lcd.setCursor(0, 1);//Set the cursor at Line 1, Column 0
  lcd.print("             ");//Here is to leave some spaces after the characters so as to clear the previous characters that may still remain.
  lcd.setCursor(9, 1);//Set the cursor at Line 1, Column 9.
  lcd.print(distance);// print on the LCD the value of the distance converted from the time between ping sending and receiving. 
  lcd.setCursor(12, 1);//Set the cursor at Line 1, Column 12.
  lcd.print("cm");//print the unit "cm"

  if(distance <= 10)
  {
    myServo1.write(180);
  }
  else if(distance > 10)
  {
    myServo1.write(0);
  }
  

}
