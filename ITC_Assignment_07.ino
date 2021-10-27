#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <EEPROM.h>
#include <TimerOne.h>

//for sound
#define buzzer 8

#define debounce 500

int h = 12 ;
int m  = 56;
int s = 4;
void setup() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLED.clearDisplay();
  //drawArea();
  Serial.begin(9600);

  //No matter which part of the program's running , if reach to 1 second excute timePass().
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timePass);

  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  h = EEPROM.read(0);
  m = EEPROM.read(sizeof(h));
  s = EEPROM.read(sizeof(m) * 2);


  OLED.display();
}

int a, b, c;
int lastPress = 0;
void loop() {
  //OLED.clearDisplay();
  OLED.setCursor(24, 14);
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);




  EEPROM.put(0, h);
  EEPROM.get(0, h);

  EEPROM.put(sizeof(h), m);
  EEPROM.get(sizeof(h), m);

  EEPROM.put(sizeof(m) * 2, s);
  EEPROM.get(sizeof(m) * 2, s);

  OLED.display();
}

void timePass()
{
  OLED.clearDisplay();
  s += 1;
 
  if (h == 24)
  {
    h = 0;
  }
  if (h < 10)
  {
    OLED.print("0");
  }
  OLED.print(h);
  OLED.print(":");

  if (m == 60)
  {
    h++;
    m = 0;
  }
  if (m < 10)
  {
    OLED.print("0");
  }

  OLED.print(m);
  OLED.print(":");

  if (s == 60)
  {
    m++;
    s = 0;
  }
  if (s < 10)
  {
    OLED.print("0");
  }

  OLED.print(s);
}
