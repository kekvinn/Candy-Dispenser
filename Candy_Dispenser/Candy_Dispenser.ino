#include <Servo.h>
#include <LiquidCrystal.h>
#include <NewPing.h>

#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define MAX_DISTANCE 400

Servo myServos[3];
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int buttonPin = 5;
int buttonState = 0;

String candies[3] = {"Skittles", "M&Ms", "Reese's Pieces"};

int selection = 0;
int Li = 16;
int Lii = 0;
int screen = 1;
int internalTimer = 0;
boolean dispensed = false;

void setup()
{
  for(int i = 0; i < 3; i++)
  {
    myServos[i].attach(i + 7);
    myServos[i].write(0);
  }

  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
}

void loop() 
{
  if(screen == 1)
  {
    detectDistance();
    actionListener(1);
  }
  else
  {
    internalTimer++;
    displaySelection();
    actionListener(2);
    delay(150);

    if(internalTimer > 10)
    {
      screen = 1;
      internalTimer = 0;
    }
  }
}

void detectDistance()
{
  unsigned int uS = sonar.ping(); 
  int distance = uS / US_ROUNDTRIP_CM;
  
  if(distance <= 8)
  {
    dispensed = true;
    displayDispensing();
    myServos[selection].write(180);
  }
  else if(distance > 8)
  {
    myServos[selection].write(0);
    if(dispensed)
    {
      displayEnjoy();
    }
    dispensed = false;
    displayDefault();
  }
}

void actionListener(int screenNum)
{
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH && dispensed == false)
  {
    lcd.clear();
    incrementSelection();

    switch(screenNum)
    {
      case 1:
        screen = 2;
        delay(150);
        break;
      case 2:
        internalTimer = 0;
        break;
    }
  }
}

void incrementSelection()
{
  if(selection != 2)
  {
    selection++;
  }
  else
  {
    selection = 0;
  }
}

void displayDefault()
{
  lcd.setCursor(0, 0);
  lcd.print("The CanDyspenser");
  lcd.setCursor(0, 1);;
  lcd.print(scrollLeft("Currently dispensing: " + candies[selection]));
  delay(150);
}

void displayDispensing()
{
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Dispensing...");
}

void displayEnjoy()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Enjoy!");
  delay(1500);
}

void displaySelection()
{
  lcd.setCursor(0, 0);
  lcd.print("Select candy:");
  lcd.setCursor(0, 1);
  lcd.print(candies[selection]);
}

String scrollLeft(String str)
{
  String result;
  String StrProcess = "                " + str + "                ";
  result = StrProcess.substring(Li, Lii);
  Li++;
  Lii++;
  if(Li > StrProcess.length())
  {
    Li = 16;
    Lii = 0;
  }
  return result;
}
