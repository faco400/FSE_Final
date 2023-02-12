#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "led.h"



#define LED_RED 23
#define LED_GREEN 22
#define LED_BLUE 21


void led_routine()
{
  while (true)
  {  
    esp_rom_gpio_pad_select_gpio(LED_RED);
    esp_rom_gpio_pad_select_gpio(LED_GREEN);
    esp_rom_gpio_pad_select_gpio(LED_BLUE);
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GREEN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_BLUE, GPIO_MODE_OUTPUT);

        // turn the LED red
    gpio_set_level(LED_RED, 1);
    gpio_set_level(LED_GREEN, 0);
    gpio_set_level(LED_BLUE, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    gpio_set_level(LED_RED, 0);
    gpio_set_level(LED_GREEN, 1);
    gpio_set_level(LED_BLUE, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    gpio_set_level(LED_RED, 0);
    gpio_set_level(LED_GREEN, 0);
    gpio_set_level(LED_BLUE, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
     
  }
}