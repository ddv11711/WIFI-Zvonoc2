  #include <WiFi.h>               //Библиотека для работы Wi-Fi
  #include <ESPAsyncWebServer.h>  //Библиотека для работы асинхронного web-интерфейса
  #include <SPIFFS.h>             //Библиотека для работы файловой системы
  #include <ArduinoJson.h>        //Библиотека для работы с json объектами

  IPAddress apIP(192, 168, 4, 1); //Ip для точки доступа 
  AsyncWebServer  HTTP(80);       //Асинхронного web-server с портом 80

  String _ssid = "RT-GPON-F280";      //Логин для подключения к Wi-Fi
  String _password = "2630826308";    //Пароль для подключения к Wi-Fi
  String _ssidAP = "Wi-Fi-Zvonoc";    //Логин для точки доступа
  String _passwordAP = "2630826308";  //Пароль для точки доступа
  String ip = "Не знаю";              //IP устрйства
  String SSDP_Name = "Wi-Fi-Zvonoc";  //Имя устройства
  String jsonConfig="{}";
  String error="";

void setup() {
     Serial.begin (115200);                //Частота порта для считывания
     Serial.println("\nStart 1-FS");       //Вспомогательная информация в com порт
     FS_init();                            //Запуск файловой системы
     Serial.println("Start 2-Fileconfig");
     loadConfig();//считывает данные из файла
     Serial.println("Start 3-Wi-Fi");       //Вспомогательная информация в com порт
     WIFI_init();                          //Запуск подключение к Wi-Fi
     Serial.println("Start 4-Webserver");  //Вспомогательная информация в com порт
     HTTP_init();                          //Запуск HTTP интерфейс
}

void loop() {
     delay(1);
}
