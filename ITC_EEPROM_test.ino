#include <EEPROM.h>
#include <TimerOne.h>

#define ledPin 13
#define buttonPin 12
#define resetButtonpin 11
#define debounce 50

byte lastButtonState = 1;
int lastPress = 0;
int counter = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(resetButtonpin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  counter = EEPROM.read(0);

//  EEPROM.write(0, 0);
}

int red,reset;
//Once out of power or stop running , counter still be the lasted value as it'been press

void loop()
{
  red = digitalRead(buttonPin);
  reset = digitalRead(resetButtonpin);
 
  
  if (millis() - lastPress >= debounce)
  {
    //press to count
    if (red == 0 && lastButtonState == 1)
    {
      counter++;
      EEPROM.put(0, counter);
      lastPress = millis();
      digitalWrite(ledPin, HIGH);
      lastButtonState = 0;

      Serial.print("Counter = ");
      Serial.println(counter);
    }

    if(red == 1 && lastButtonState == 0)
    {
      digitalWrite(ledPin, LOW);
      lastButtonState = 1;
    }

    //reset section
     if (reset == 0)
    {
      counter=0;
       EEPROM.put(0, counter);
    }
  }

}
