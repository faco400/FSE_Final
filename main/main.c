#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#include "wifi.h"
#include "mqtt.h"
#include "dht11.h"

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

void trataComunicacaoComServidor(void *params)
{
  char mensagem[50];

  if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while (true)
    {
      float temperatura = 20.0 + (float)rand() / (float)(RAND_MAX / 10.0);
      sprintf(mensagem, "{\"temperatura1\": %f}", temperatura);
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
      //  mqtt_envia_mensagem("sensores/temperatura", mensagem);

      // sprintf(JsonAtributos,"{\"quantidade de pinos\": 5,\n\"umidade\": 20}");
      // mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtributos);

      vTaskDelay(3000 / portTICK_PERIOD_MS);
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

void app_main(void)
{
  // Inicializa o NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  wifi_start();

  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
  xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
  xTaskCreate(&leitura_dht11_temp_umidade, "Leitura de Umidade e temperatura do sensor DHT11", 4096, NULL, 1, NULL);
}
