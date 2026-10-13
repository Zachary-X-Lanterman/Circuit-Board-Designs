// C++ code
//
#include "Adafruit_LEDBackpack.h"

const int seqLen = 200;
int sequence[seqLen];
int i = 0;
int score = 0;

bool redPressed = false;
bool greenPressed = false;
bool yellowPressed = false;
bool bluePressed = false;

Adafruit_7segment led_display1 = Adafruit_7segment();

void setup()
{
  led_display1.begin(112);
  /*Serial.begin(9600);
  Serial.print("\n\n\n\n\n");*/
  
  pinMode(A0,INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  
  randomSeed(analogRead(1));

  //showSequence();
}

void loop()
{
  //led_display1.show(score);
  
  led_display1.println(score);
  led_display1.writeDisplay();
  
  sequence[score] = random(2,6);//pins 2-5, LEDS
  
  showSequence();
  
  for (i = 0; i <= score; i++)
  {
    int lastPressed = awaitButton();
    Serial.print(lastPressed);
	
    if (lastPressed != sequence[i])
    { //Game Over Logic
      digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      tone(13, 100);
      while (true){}
    }
  }
  score++;

}

void showSequence()
{
  delay(500);
  for (i = 0; i <= score; i++)
  {
    digitalWrite(sequence[i],HIGH);
    tone(13, sequence[i] * 100, 500);
    delay(analogRead(A0) + 20);
    digitalWrite(sequence[i],LOW);
    delay(100);
  }
}


//this will halt the program until a button is pressed
//when a button is pressed, it will return its corresponding LED

//this is a bit of a clunky way to implement it,
//but it flashes the corresponding LED when a button is pressed
//and deals with debounce.

//I wish I could clean this code up, but when I tried
//TinkerCAD gave me an 'invalid header file' error for no reason
//Literally, it was working and then randomly stopped. Too bad!
int awaitButton()
{
  while (true)
  {
  	if (digitalRead(6) == HIGH && redPressed == false)
    {
      	digitalWrite(2,HIGH);
      	redPressed = true;
      	tone(13,200);
      
      	while (digitalRead(6) == HIGH)
        {//this empty loops halts the program untill
        }//the button is unpressed.
      	noTone(13);
        digitalWrite(2,LOW);
        redPressed = false;         
        return 2;
    }
    
    if (digitalRead(7) == HIGH && greenPressed == false)
    {
      	digitalWrite(3,HIGH);
      	greenPressed = true;
      tone(13,300);
      
      	while (digitalRead(7) == HIGH)
        {
        }
        noTone(13);
        digitalWrite(3,LOW);
        greenPressed = false;         
        return 3;
    }
    
    if (digitalRead(8) == HIGH && greenPressed == false)
    {
      	digitalWrite(4,HIGH);
      	yellowPressed = true;
      tone(13,400);
      
      	while (digitalRead(8) == HIGH)
        {
        }
        noTone(13);
        digitalWrite(4,LOW);
        yellowPressed = false;         
        return 4;
    }
    
    if (digitalRead(9) == HIGH && bluePressed == false)
    {
      	digitalWrite(5,HIGH);
      	bluePressed = true;
        tone(13,500);
      
      	while (digitalRead(9) == HIGH)
        {
        }
        noTone(13);
        digitalWrite(5,LOW);
        bluePressed = false;         
        return 5;
    }
  }
}
