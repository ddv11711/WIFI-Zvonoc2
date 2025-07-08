void FS_init(){                                                                //Инициализация FFS
     if(!SPIFFS.begin(true)) Serial.println("ERROR SPIFFS");                   //Если файловой системы нет выводим ошибку и создаём новую
}

String getContentType (String filename){                                       //Функции для автоматического определения типа файла
       if (filename.endsWith (".htm"))  return "text/html";                    //Возврат для файла типа htm
       else if (filename.endsWith (".html")) return "text/html";               //Возврат для файла типа html
       else if (filename.endsWith (".json")) return "application/json";        //Возврат для файла типа json
       else if (filename.endsWith (".css"))  return "text/css";                //Возврат для файла типа css
       else if (filename.endsWith (".js"))   return "application/javascript";  //Возврат для файла типа js
       else if (filename.endsWith (".png"))  return "image/png";               //Возврат для файла типа png
       else if (filename.endsWith (".gif"))  return "image/gif";               //Возврат для файла типа gif
       else if (filename.endsWith (".jpg"))  return "image/jpg";               //Возврат для файла типа jpg
       else if (filename.endsWith (".ico"))  return "image/x-icon";            //Возврат для файла типа ico
       else if (filename.endsWith (".xml"))  return "text/xml";                //Возврат для файла типа xml
       else if (filename.endsWith (".pdf"))  return "application/x-pdf";       //Возврат для файла типа pdf
       else if (filename.endsWith (".zip"))  return "application/x-zip";       //Возврат для файла типа zip
       else if (filename.endsWith (".gz"))   return "application/x-gzip";      //Возврат для файла типа gz
       return "text/plain";                                                    //Возврат по умолчаню
}
