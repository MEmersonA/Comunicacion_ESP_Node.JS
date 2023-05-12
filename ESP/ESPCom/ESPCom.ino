#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "KinaWifi";
const char* password = "L@wrence7590";

String url;
String httpRequestData,payload;
short int httpResponseCode;

char json[500];
DynamicJsonDocument doc(1024);

int temperatura;
int binLed = 0;
String bl = "0000";
int mode = 0;

const int leds[4] = {13, 12, 14, 27};

void setup() {
 
  Serial.begin(115200);

  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[2], OUTPUT);
  pinMode(leds[3], OUTPUT);
  
  Serial.print("Conectando");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

}
void Enviar(){
  HTTPClient http;
  http.addHeader("Content-Type", "text/plain");
  url = "http://192.168.1.35/Sensor?temperatura="+(String)temperatura+"&key=esp";
  http.begin(url);
  httpResponseCode = http.GET();
  delay(300);
  if (httpResponseCode == 200) {
    
    Serial.print("Se ha enviado: ");
    Serial.print(temperatura);
    Serial.println("C");

  }else{

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

  }
  http.end();
}

void Recibir(){

  HTTPClient http;

  http.addHeader("Content-Type", "text/plain");
  url = "http://192.168.1.35/Enviar?key=esp";
  http.begin(url);
  httpResponseCode = http.GET();
  String payload = http.getString();
  delay(300);
  if (httpResponseCode == 200) {

    payload.toCharArray(json, 500);
    deserializeJson(doc, json);
    
    binLed = doc["binLed"];
    mode = doc["mode"];

    Serial.print("Se ha recibido binLed: ");
    Serial.println(binLed);
    Serial.print("Se ha recibido mode: ");
    Serial.println(mode);


  }else{

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

  }

  http.end();

}

void Temperatura(){
    temperatura = random(0, 10);
}

void Led(){

  if(mode == 1){

    bl = binLed;

    for(int x = 0; x < 4; x++){

      if(bl.length() < 4){
        bl = "0"+bl;
      }

    }

    for(int x = 0; x < 4; x++){

      if(bl.charAt(x) == '1'){
        digitalWrite(leds[x], HIGH);
      }else{
        digitalWrite(leds[x], LOW);
      }

    }

  }

  if(mode == 0){

    switch(binLed){
      case 0:
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[3], HIGH);
        break;
      case 1:
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[2], HIGH);
        digitalWrite(leds[3], LOW);
        break;
      case 2:
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], HIGH);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[3], LOW);
        break;
      case 3:
        digitalWrite(leds[0], HIGH);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[3], LOW);
        break;
    }

  }

}

void loop() {

  Temperatura();
  Enviar();
  Recibir();
  Led();

  delay(1000);
}