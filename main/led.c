#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "led.h"

#define LED 2

void led_esp(int value)
{
  esp_rom_gpio_pad_select_gpio(LED);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  gpio_set_level(LED, value);
 
}