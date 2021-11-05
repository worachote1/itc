#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED     6 //8
#define YELLOW  7 //9
#define GREEN   8 //10

#define SW1     12 //5  //control red
#define SW2     11 //6  //control yellow
#define SW3     10 //7  //control green

QueueHandle_t BlinkQueue;

void setup()
{
  Serial.begin(9600);  
  BlinkQueue =  xQueueCreate(10, sizeof(int32_t));
  
  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW1, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW2, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW3, 1, NULL);
  
  xTaskCreate(vReceiverTask, "Receiver Task ", 100, RED, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, YELLOW, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, GREEN, 1, NULL);
}

void vSenderTask(void *pvParameters) 
{
  BaseType_t qStatus;
  int32_t valueToSend = 0;
  int SW = (int32_t)pvParameters;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(SW, INPUT_PULLUP);
  while (1)
  {
    if (digitalRead(SW) == LOW)
      valueToSend = SW;
    else
      valueToSend = 0;

    if (valueToSend )
    {
      qStatus = xQueueSend(BlinkQueue, &valueToSend, xTicksToWait);
      vTaskDelay(10);
    }
  }
}

void vReceiverTask(void *pvParameters)
{
  int LED = (int32_t)pvParameters;
  int32_t valueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  //these LED are active LOW (LED active when LOW)
  pinMode(RED, OUTPUT); digitalWrite(RED, HIGH);
  pinMode(YELLOW, OUTPUT); digitalWrite(YELLOW, HIGH);
  pinMode(GREEN, OUTPUT); digitalWrite(GREEN, HIGH);
  
  bool YELLOW_status = false;
  while (1)
  {
    qStatus = xQueueReceive(BlinkQueue, &valueReceived, xTicksToWait);
    if (qStatus  == pdPASS)
    {
      Serial.println(valueReceived);
      if (valueReceived == 12 && LED == RED)
      {
        digitalWrite(RED, 0);
        vTaskDelay(150);
        digitalWrite(RED, 1);
      }
      else if (valueReceived == 11 && LED == YELLOW)
      {
        YELLOW_status = !YELLOW_status;
      }
      else if (valueReceived == 10 && LED == GREEN)
      {
        digitalWrite(GREEN, 0);
        vTaskDelay(50); //คล้ายๆ delay(500)
        digitalWrite(GREEN, 1);
        vTaskDelay(50);
        digitalWrite(GREEN, 0);
        vTaskDelay(50);
        digitalWrite(GREEN, 1);
        vTaskDelay(50);
        digitalWrite(GREEN, 0);
        vTaskDelay(50);
        digitalWrite(GREEN, 1);
        vTaskDelay(50);
      }
      else if (valueReceived != 10)
      {
        int32_t valueReceived = valueReceived;
        xQueueReceive(BlinkQueue, &valueReceived, xTaskCreate);
        vTaskDelay(1);
      }
    }
    if (YELLOW_status && LED == YELLOW)
    {
      digitalWrite(YELLOW, LOW);
      vTaskDelay(20);
      digitalWrite(YELLOW, HIGH);
      vTaskDelay(20);
    }
  }
}
void loop() {}
