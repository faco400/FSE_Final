#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#include "wifi.h"
#include "mqtt.h"
#include "dht11.h"
#include "led.h"
// #include "lum.h"
#include "pwm.h"
#include "nvs.h"

#define ENERGY_MODE CONFIG_ENERGY_MODE
#define BATTERY_MODE CONFIG_BATTERY_MODE


SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

void conectadoWifi(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}


void leitura_dht11_temp_umidade()
{
  char msg[50];
  DHT11_init(GPIO_NUM_4);

  while (1)
  {

    float temperatura = DHT11_read().temperature;
    float umidade = DHT11_read().humidity;

    if (temperatura != -1 && umidade != -1)
    {

      printf("Temperatura: %.2f\n", temperatura);
      printf("Umidade:  %.2f\n", umidade);

      sprintf(msg, "{\"Temperatura\": %f}", temperatura);
      mqtt_envia_mensagem("v1/devices/me/telemetry", msg);

      sprintf(msg, "{\"Umidade\": %f}", umidade);
      mqtt_envia_mensagem("v1/devices/me/telemetry", msg);

      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
}

void modo_energia()
{
  xTaskCreate(&leitura_dht11_temp_umidade, "Leitura de Umidade e temperatura do sensor DHT11", 2048, NULL, 1, NULL);
}

void modo_low_power()
{
  xTaskCreate(&led_routine, "Rotina da led ESP32", 4096, NULL, 1, NULL);
}

void trataComunicacaoComServidor(void *params)
{

  if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    #ifdef CONFIG_ENERGY_MODE
      ESP_LOGI("MODE", "Acionando modo de energia");
      modo_energia();
    #else
      ESP_LOGI("MODE", "Acionando modo de bateria(low power)");
      modo_low_power();
    #endif
  }
  vTaskDelete(NULL);
}

void app_main(void)
{
  inicia_nvs();

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  config_pwm();
  wifi_start();

  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
  xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
}
