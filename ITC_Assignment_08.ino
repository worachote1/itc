#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN    8

#define debounce 50

#define button_R  12
#define button_Y  11
#define button_G  10

int lastPress = 0;
int r, g, y;
void setup()
{
  Serial.begin(9600);

  pinMode(button_R, INPUT_PULLUP);
  pinMode(button_Y, INPUT_PULLUP);
  //  pinMode(button_G, INPUT_PULLUP);

  xTaskCreate(redLedControllerTask, "RED LED Task", 128, NULL, 1, NULL);
  xTaskCreate(greenLedControllerTask, "BLUE LED Task", 128, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "YELLOW LED Task", 128, NULL, 1 , NULL);

}

//เมื่อกด button_R ให้ LED นี้ติดเป็นเวลา 3 วินาทีแล้วดับ ถ้ากดซํ้าระหว่างที่ติดให้นับเวลาจากที่กดไปอีก 3 วินาที
//(เช่น กดไปแล้ว 2 วิ อีกวินึงมันจะหมดถูกมะ แล้วเรากดอีกรอบพอดีก็ +3 ติดให้ครบ 6 วิ)
void redLedControllerTask(void *pvParameters)
{
  pinMode(RED, OUTPUT);
  String r_state = "OFF";

  while (1)
  {
    r = digitalRead(button_R);


  }
}
//จะอ่านสถานะของ LED (ใช้คำสั่ง digitalRead) จากนั้นนำมา xor (ในภาษา C การทำ xor จะใช้เครื่องหมาย ^) กับ 1 ทำให้เมื่ออ่านได้ 1 จะกลายเป็น 0
//และหากอ่านได้ 0 จะกลายเป็น 1 ทำให้เมื่อเขียนกลับไปที่ LED ผ่านคำสั่ง digitalWrite
//จะทำให้กลับสถานะ คือ จาก 0 ก็จะเขียนกลับเป็น 1 และจาก 1 ก็จะเขียนกลับเป็น 0 ซึ่งก็คือไฟกระพริบนั่นเอง


//เมื่อกด button_Y ให้ LED นี้ติดและกระพริบไปเรื่อยๆ จนกว่าจะกด button_Y อีกคร้ง

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  pinMode(button_Y, INPUT_PULLUP);
  String y_state = "OFF";
  while (1)
  {
    y = digitalRead(button_Y);
 
    
    if (y == 0 && millis() - lastPress >= debounce)
    {
      lastPress = millis();
      if (y_state == "OFF")
      {
        y_state = "ON";
      }
      else if (y_state == "ON")
      {
        y_state = "OFF";
      }
    }
    
     if (y_state == "ON")
    {
     // delay(500);
      digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
    }
    else if(y_state == "OFF")
    {
      digitalWrite(YELLOW, HIGH); // turn off LED (this is active LOW , LED will turn on when LOW)
    }

    Serial.print("y_state = ");
    Serial.println(y_state);
  }
}

//กด button_G แล้ให้ LED นี้กระพริบ 3 ครั้งครั้งละ 500 ms ถ้ากดซํ้าไม่มีผล(ต้องกระพริบให้ครบถึงกดใหม่ได้)
void  greenLedControllerTask(void *pvParameters)
{
  pinMode(GREEN, OUTPUT);
  pinMode(button_G, INPUT_PULLUP);
  String g_state = "OFF";
  while (1)
  {

    digitalWrite(GREEN, HIGH); //led light when LOW (active LOW)
    g = digitalRead(button_G);
    if (g == 0 && millis() - lastPress >= debounce)
    {
      lastPress = millis();
      if (g_state == "OFF")
      {
        g_state = "ON";
      }
      else if (g_state == "ON")
      {
        g_state = "OFF";
      }
    }

    if (g_state == "ON")
    {
      for (int i = 1 ; i <= 3 ; i++)
      {
        //        digitalWrite(GREEN, HIGH);
        //        delay(500);
        //        digitalWrite(GREEN, LOW);
        //        delay(500);

        digitalWrite(GREEN, digitalRead(GREEN) ^ 1);
        delay(500);
        digitalWrite(GREEN, digitalRead(GREEN) ^ 1);
        delay(500);
      }
      g_state = "OFF";
    }


  }
}

void loop()
{


}
