#include "freertos/FreeRTOS.h"
#include "driver/ledc.h"

#include "pwm.h"
#include "led.h"
#include "nvs.h"

#define LED_RED 23
#define LED_GREEN 22
#define LED_BLUE 21

void config_pwm()
{


  // Configuração do Timer
  ledc_timer_config_t timer_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_8_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = 1000,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&timer_config);

  // Configuração dos Canais
  ledc_channel_config_t channel_config = {
      .gpio_num = LED_RED,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&channel_config);

    
  ledc_channel_config_t channel_config1 = {
      .gpio_num = LED_GREEN,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_1,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&channel_config1);

  
  ledc_channel_config_t channel_config2 = {
      .gpio_num = LED_BLUE,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_2,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&channel_config2);

  
}




void set_pwm_red(int value)
{
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, value * 2.5);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
  grava_valor_nvs("setRed", value);
}

void set_pwm_green(int value)
{
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, value * 2.5);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
  grava_valor_nvs("setGr", value);
}

void set_pwm_blue(int value)
{
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, value * 2.5);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);
  grava_valor_nvs("setBl", value);
}