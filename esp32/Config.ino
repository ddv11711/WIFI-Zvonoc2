bool loadConfig(){
     File configFile=SPIFFS.open("/config.json","r");//открываем файл для чтения
     if (!configFile){//если файл не найден
        configFile.close();
        Serial.println("Filed to open config file");
        saveConfig();//создаём файл записав в него значения по умолчанию
        return false;
     }
     size_t size = configFile.size();//проверяем размер файла будем использовать файл меньше 1024 байта
     if (size > 1024 || size<1){//eсли файл больше то выдаём ошибку/////////////////провести максимальную нагрузку
        configFile.close();
        Serial.println("Config file size is too large");
        saveConfig();//создаём файл записав в него значения по умолчанию
        return false;
     }
     jsonConfig = configFile.readString();//сохраняем файл в глобальную переменную
     Serial.println(jsonConfig);
     configFile.close();
     DynamicJsonBuffer jsonBuffer;//выделяем память для json объекта
     //вызываем парсер JSON через экземпляр jsonBuffer
     //строку возьмём из глобальной памяти String jsonConfig
     JsonObject&root = jsonBuffer.parseObject(jsonConfig);
     //теперь можно получить значения из doc
     SSDP_Name = root["SSDPName"].as<String>();
     return true; 
}

bool saveConfig(){
     DynamicJsonBuffer jsonBuffer; //резервируем память для json объекты  
     JsonObject&json=jsonBuffer.parseObject(jsonConfig);//выводим парсер JSON через экземпляр jsonBuffer
     //заполняем поля json
     json["SSDPName"] = SSDP_Name;
     File configFile= SPIFFS.open("/config.json","w");//открываем файл для записи
     if (!configFile){
        Serial.println("Failed to open config file for writing");
        error+="Ошибка при открытии файла config.json пожалуйста проверьте свои настройки ";
        configFile.close();
        return false;
     }
     json.printTo(configFile);//записываем строку json в файл
     configFile.close();
     return true;
}
