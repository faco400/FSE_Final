#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "esp32/rom/uart.h"

#include "led.h"

#define LED 2
#define BOTAOESP 0

void led_esp(int value)
{
  esp_rom_gpio_pad_select_gpio(LED);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  gpio_set_level(LED, value);
 
}

void led_routine()
{
  led_esp(0);
  for(int estado = 0;;estado = !estado)
  {
    if(rtc_gpio_get_level(BOTAOESP) == 0)
    {
      printf("Aguardando soltar o botao\n");
      do
      {
        vTaskDelay(pdMS_TO_TICKS(10));
      }while(rtc_gpio_get_level(BOTAOESP) == 0);
    }

    gpio_set_level(LED, estado);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    // esp_light_sleep_start();
  }
}