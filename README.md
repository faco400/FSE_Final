# Fundamentos de Sistemas Embarcados - Trabalho Final

O objetivo deste trabalho é criar sensores e atuadores distribuídos baseados nos microcontroladores ESP32 interconectados via Wifi através do protocolo MQTT. Em nosso contexto, utilizamos o sensor DHT11 para aferir a temperatura ambiente
em ºC e a umidade relativa do ar em %. Além disso, um led  rgb foi utilizado, sendo possivel realizar o controle PWM de cada uma das cores RGB do sensor, formando assim  cores diversas e em diferentes intensidades a depender das intensidade de cada cor presente em cada botão na DashBoard. Também foi implementada a ativação/desativação  do led da própria ESP32 com os botões presentes na dashboard.




## Plataforma utilizada

Este trabalho foi realizado utilizando a Espressif através da [ESP-IDF VS Code Extension](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#) .

## Como rodar a aplicação

- Clonar ou baixar os arquivos do repositório

- Instalar o [ESP-IDF VS Code Extension](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#) 
- Abrir os arquivos do projeto no VSCode

- Abrir o ESP-IDF Terminal no menu inferior do vscode e configurar as credenciais de Wifi com o seguinte comando: 

```bash
idf.py menuconfig
```
- Conectar a ESP32 via cabo USB no Computador/Notebook

- Utilizar  a opção no menu inferior do VSCode para fazer o Build, Flash e Monitor , iniciando assim a comunicação da ESP32 com  a DashBoard configurada.


## DashBoard

Nome: KayroViniciusVieira

![dahsboard](https://raw.githubusercontent.com/faco400/FSE_Final/main/img/dash.png)