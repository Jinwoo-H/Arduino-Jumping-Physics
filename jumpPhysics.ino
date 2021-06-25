//Declarations for OLED Screen
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Our own definitions for the game board
#define LED 10
#define BUTTON1 12
#define BUTTON2 11
#define PEIZO 8
#define JOY_X A6
#define JOY_Y A7

int ballX = 10;
int ballY = 54;
int veloX = 0;
int veloY = 0;

int groundState = 1;
int jumpState = 0;

int platState = 0;

int level = 1;
int lives = 1;


int joyX, joyY, buttonState1, buttonState2;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //Start up and initialize the display
  
  pinMode(LED,OUTPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(PEIZO,OUTPUT);
  pinMode(JOY_X,INPUT);
  pinMode(JOY_Y,INPUT);

  //Clear the display buffer once to start up our screen
  display.clearDisplay();
  display.display();
}

int velocity(int joyX, int joyY)
{
  if (joyX > 560)
  {
    if (veloX <= 2)
    {
      veloX++;
    }
  }
  else if (joyX < 470)
  {
    if (veloX >= -2)
    {
      veloX--;
    }
  }
  else
  {
    if (veloX > 0)
    {
      veloX--;
    }
    if (veloX < 0)
    {
      veloX++;
    }
  }
  return(veloX);  
}

void loop() {
  display.clearDisplay();
  
  joyX = analogRead(JOY_X);
  joyY = analogRead(JOY_Y);

  int lastState1 = buttonState1;
  buttonState1 = digitalRead(BUTTON1);
  buttonState2 = digitalRead(BUTTON2);

  veloX = velocity(joyX, joyY); //function for player movement

  if (buttonState1 == HIGH && lastState1 == LOW)
  {
    //Serial.println("bruh");
    jumpState = 1;
  }
  if (jumpState == 1)
  {
    if (veloY == 0 && groundState == 1) //start of jump
    {
      groundState = 0;
      veloY = 6;
    }

    else if (ballY >= 54 && groundState == 0 && veloY == -3) //ball hit ground
    {
      ballY = 54;
      veloY = 0;
      groundState = 1;
      jumpState = 0;
    }
    else if (veloY > -3 && groundState == 0)
    {
      veloY--;
    }
  }

  if (ballX < 0)
  {
    veloX = 0;
    ballX = 0;
  }
  
  ballX += veloX;
  ballY -= veloY;
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  //display.print("Level: ");
  //display.println(level);
  /*display.print(veloX);
  display.print(" ");
  display.println(ballX);
  display.print(veloY);
  display.print(" ");
  display.println(ballY);*/
  display.fillRect(0,59,128,5,WHITE);
  display.fillRect(ballX, ballY, 5, 5, WHITE);
  //Serial.println(platState);


  display.display();
}
