

#include <Arduino_FreeRTOS.h>
#include "semphr.h"//create handle for the mutex. It will be used to referencemutex
SemaphoreHandle_t xMutex;
void setup()
{
  Serial.begin(9600);
  xMutex= xSemaphoreCreateMutex();
  xTaskCreate(OutputTask,"Printer Task 1", 100,"Task 1 \r\n",1,NULL);
  xTaskCreate(OutputTask,"Printer Task 2", 100,"Task 2 \r\n",2,NULL);    
//  Serial.print("portMAX_DELAY = ");
//  Serial.print(portMAX_DELAY);
// portMAX_DELAY = 65535
}

void OutputTask(void *pvParameters)
{
  char *pcStringToPrint;
  pcStringToPrint= (char *)pvParameters;
  while(1){
    printer(pcStringToPrint);
    vTaskDelay(pdMS_TO_TICKS(100));
    }
 }
 // this printer task send data to arduino serial monitor
 //also it is shared resource between both instances of the tasks
 void printer(const char* pcString)
 {// take mutex
  xSemaphoreTake(xMutex, 65536); //portMAX_DELAY
  Serial.println(pcString); // send string to serial monitor
  xSemaphoreGive(xMutex); // release mutex}
 }
 void loop()
 {
 
 }
