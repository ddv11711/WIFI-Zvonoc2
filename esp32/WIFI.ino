void WIFI_init (){                                                 //Инициализация Wi-Fi
     WiFi.mode (WIFI_STA);                                         //Режим подключения к Wi-Fi
     byte tries = 11;                                              //Количество попыток подключения 
     Serial.println ("ssid:" + _ssid + " password:" + _password);  //Вспомогательная информация в com порт
     WiFi.begin (_ssid.c_str(), _password.c_str());                //Подключение к Wi-Fi 
     while (--tries && WiFi.status() != WL_CONNECTED){             //В цикле проверяем статус подключения
           Serial.print (".");                                     //Вспомогательная информация в com порт
           delay (1000);                                           //Ожидание в 1 секунду между проверками
     }
     Serial.println("");
     
     if (WiFi.status() == WL_NO_SSID_AVAIL)                        //Ошибка если сеть не найдена
        ip = "Сеть не найдена";                                    //Сохроняем текс ошибки
     else if (WiFi.status() == WL_DISCONNECTED)                    //Ошибка если неправильный пароль
             ip="Неправильный пароль";                             //Сохроняем текс ошибки
     else if(WiFi.status() == WL_CONNECTED){                       //Если удалось подключится то выводим IP
          Serial.println ("Wi-Fi Connected");                      //Вспомогательная информация в com порт
          ip = WiFi.localIP ().toString();                         //Cохраняем полученный IP
          /*dnsServer.setTTL(300);
          dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
          dnsServer.start(DNS_PORT,"zvonoc.com",WiFi.localIP());*/
     }
     Serial.println (ip);                                          //Выводим полученный IP или текст ошибки
     if (WiFi.status() != WL_CONNECTED)                            //Если не удалось подключится подымаем точку доступа
        StartAPMode ();                                            //Запуск режима точки доступа
}

void StartAPMode (){                                               //Функция для запуска локайлой точки точки зрения
     WiFi.disconnect ();                                           //Отключаемся от Wi-Fi
     WiFi.mode (WIFI_AP);                                          //Включаем режим точки доступа
     WiFi.softAPConfig (apIP, apIP, IPAddress (255,255,255,0));    //Указываем шлюз IP и маску
     WiFi.softAP (_ssidAP.c_str(), _passwordAP.c_str());           //Указываем логи и пароль для точки доступа
     Serial.println ("Wi-Fi up AP");                               //Вспомогательная информация в com порт
     ip=apIP.toString();                                           //Cохраняем локальный IP
     Serial.println (ip);                                          //Выводим локальный IP
     // dnsServer.start (DNS_PORT, "*", apIP);                     //Включаем переодрисацию всех запросов на сервер
}
