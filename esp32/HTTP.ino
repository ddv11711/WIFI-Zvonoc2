void HTTP_init (){                                                                //Логика web-интерфейса
     HTTP.on ("/restart", HTTP_GET, handle_Restart);                              //Перезагрузка модуля по запросу http://192.168.4.1/restart?device=ok
     HTTP.on ("/", HTTP_GET, handle_index);                                       //Главная страница
     HTTP.on ("/css/index.css", HTTP_GET, handle_indexcss);                       //Стили к главной странице
     HTTP.on ("/img/favicon.ico", HTTP_GET, handle_favicon);                      //Картинка для строки поиска
     HTTP.on ("/setup.html", HTTP_GET, handle_setup);                             //Страница настроек
     HTTP.on ("/css/style.css", HTTP_GET, handle_setupcss);                       //Стили для страницы настроек
     HTTP.on ("/js/function.js", HTTP_GET, handle_function);                      //Файл со скриптами для страницы настроек
     HTTP.on ("/ssdp", HTTP_POST, handle_set_ssid);                               //Пост запрос для сохраниения SSDP_Name
     HTTP.onNotFound (handleNotFound);                                            //Если страница не найдена
     HTTP.begin ();                                                               //запуск HTTP сервера
}

void handle_Restart (AsyncWebServerRequest *request){                             //Функция для перезагрузки модуля
     //String restart = request->arg ("device");                                  //Получение аргумета из запросса device
     request->send (200, "text/plain", "OK");                                     //Ответ клиенту о том что запрос получен успешно
     if (request->arg ("device") == "ok") ESP.restart();                          //Если аргумент верен перезапускаем устройство
}

void handle_index (AsyncWebServerRequest *request){                               //Функция для ответа на запрос о галвной страницы
     request->send (SPIFFS, "/index.html", "text/html", false, processor_index);  //Ответ на запрос стримом файла
}

void handle_indexcss (AsyncWebServerRequest *request){                            //Функция для ответа на запрос о файле стилей для главной страницы
     request->send(SPIFFS, "/css/index.css", "text/css");                         //Ответ на запрос стримом файла
}

void handle_favicon (AsyncWebServerRequest *request){                             //Функция для ответа на запрос о картинки для строки поиска
     request->send(SPIFFS, "/img/favicon.ico", "image/x-icon");                   //Ответ на запрос стримом файла
}

void handle_setup (AsyncWebServerRequest *request){                               //Функция для ответа на запрос о файле настроек
     request->send(SPIFFS, "/setup.html", "text/html", false, processor_setup);   //Ответ на запрос стримом файла
}

void handle_setupcss (AsyncWebServerRequest *request){                            //Функция для ответа на запрос о файле стилей для файла настройки
     request->send(SPIFFS, "/css/style.css", "text/css");                         //Ответ на запрос стримом файла
}

void handle_function (AsyncWebServerRequest *request){                            //Функция для ответа на запрос о файле скриптов для файла настройки
     request->send(SPIFFS, "/js/function.js", "application/javascript");          //Ответ на запрос стримом файла
}

/*POST запрос*/
void handle_set_ssid (AsyncWebServerRequest *request){                            //Функция для получения и сохронения SSDP_Name
     SSDP_Name = request->arg ("ssdp");                                           //Получение аргумета из запросса ssdp
     saveConfig();                                                                //Сохраняем во внутреннюю память
     request->send(200,"text/plain","OK");                                        //Ответ клиенту о том что запрос получен успешно
}
/**/

void handleNotFound (AsyncWebServerRequest *request){                             //Функция для ответа на запрос если файл не найден
     request->send (404, "text/plain", "File Not Found");                         //Ответ на запрос ошибкой
}

String processor_index (const String& var) {                                      //Функция для изменения главной страницы 
       if (var == "SSDP")return SSDP_Name;                                        //Заменяем SSDP
       else if (var == "flag")return String(2);                                   //Заменяем флаг
       return String();                                                           //Если нет совпадений воращаем пустую строку
}

String processor_setup (const String& var){                                       //Функция для изменения страницы настройки
       if (var == "SSDP")return SSDP_Name;                                        //Заменяем SSDP
       return String();                                                           //Если нет совпадений воращаем пустую строку
}
