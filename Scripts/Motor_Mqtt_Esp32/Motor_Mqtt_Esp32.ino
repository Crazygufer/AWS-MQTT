#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "DHT.h"
#include "esp_adc_cal.h"
#include "conf.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <WiFi.h> 

//el programa está desarrollado para usar un MPU6050 y un DHT22 

// Definir pines y tipo de sensor DHT
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inicializamos el sensor MPU6050
Adafruit_MPU6050 mpu;

// Definir topico de publicacion
#define AWS_IOT_PUBLISH_TOPIC   "sitewise/ingest"
#define AWS_IOT_SUBSCRIBE_TOPIC "sitewise/ingest"

const char* ntpServer = "pool.ntp.org";

String payload;
float pay_x;
float pay_y;
float pay_z;
float pay_temp;
float pay_hum;
long tiempo;

// Inicializamos cliente de MQTT
WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

// Función que obtiene la hora actual
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return(0);
  }
  time(&now);
  return now;
}

// Conectar a AWS IoT
void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Conectando a Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Configurar WiFiClientSecure para usar las credenciales 
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  Serial.print("Conectando a AWS IOT");
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  Serial.println("AWS IoT Conectado!");
}

void setup() {
  Serial.begin(9600);
  configTime(0, 0, ntpServer);
  
  // Conectar a WiFi y AWS
  connectAWS();  

  // Inicializamos el sensor DHT22
  dht.begin();
  
  // Inicializamos el sensor MPU6050
  if (!mpu.begin()) {
    Serial.println("No se pudo encontrar el MPU6050");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
}

void loop() {
  // Obtener datos del MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  pay_x = a.acceleration.x;
  pay_y = a.acceleration.y;
  pay_z = a.acceleration.z;

  Serial.print("X: "); Serial.print(pay_x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(pay_y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(pay_z); Serial.println("  m/s^2 ");

  // Leer la temperatura y humedad del DHT22
  pay_temp = dht.readTemperature();
  pay_hum = dht.readHumidity();
  
  if (isnan(pay_temp) || isnan(pay_hum)) {
    Serial.println("Error al leer el DHT22");
    pay_temp = 0.0;  // Asignar un valor por defecto si la lectura falla
    pay_hum = 0.0;
  } else {
    Serial.print("Temperatura: "); Serial.print(pay_temp); Serial.println(" ºC");
    Serial.print("Humedad: "); Serial.print(pay_hum); Serial.println(" %");
  }

  // Obtener tiempo
  tiempo = getTime();
  
 // Publicar datos de temperatura
payload = "{\"propertyAlias\":\"/PlantaA/motor1/temp\",\"value\":";
payload += String(pay_temp);  // No usar c_str() aquí para que se mantenga como número
payload += ",\"timeInSeconds\":";
payload += String(tiempo);  // El tiempo también debe ser un número
payload += "}";
Serial.println(payload);
client.publish(AWS_IOT_PUBLISH_TOPIC, (char*)payload.c_str());

// Publicar datos de humedad
payload = "{\"propertyAlias\":\"/PlantaA/motor1/humidity\",\"value\":";
payload += String(pay_hum); // No usar c_str() aquí para que se mantenga como número
payload += ",\"timeInSeconds\":";
payload += String(tiempo);  // El tiempo también debe ser un número
payload += "}";
client.publish(AWS_IOT_PUBLISH_TOPIC, (char*)payload.c_str());

// Publicar datos de aceleración X
payload = "{\"propertyAlias\":\"/PlantaA/motor1/vibra_x\",\"value\":";
payload += String(pay_x); // No usar c_str() aquí para que se mantenga como número
payload += ",\"timeInSeconds\":";
payload += String(tiempo);  // El tiempo también debe ser un número
payload += "}";
client.publish(AWS_IOT_PUBLISH_TOPIC, (char*)payload.c_str());

// Publicar datos de aceleración Y
payload = "{\"propertyAlias\":\"/PlantaA/motor1/vibra_y\",\"value\":";
payload += String(pay_y); // No usar c_str() aquí para que se mantenga como número
payload += ",\"timeInSeconds\":";
payload += String(tiempo);  // El tiempo también debe ser un número
payload += "}";
client.publish(AWS_IOT_PUBLISH_TOPIC, (char*)payload.c_str());

// Publicar datos de aceleración Z
payload = "{\"propertyAlias\":\"/PlantaA/motor1/vibra_z\",\"value\":";
payload += String(pay_z); // No usar c_str() aquí para que se mantenga como número
payload += ",\"timeInSeconds\":";
payload += String(tiempo);  // El tiempo también debe ser un número
payload += "}";
client.publish(AWS_IOT_PUBLISH_TOPIC, (char*)payload.c_str());

delay(5000); // Enviar cada 5 segundos
}
