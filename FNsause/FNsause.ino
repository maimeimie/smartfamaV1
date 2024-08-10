#define BLYNK_TEMPLATE_ID "TMPL6bxBLVsc-"
#define BLYNK_TEMPLATE_NAME "smart farm"
#define BLYNK_AUTH_TOKEN "8w3OQsJvX4SyBpMriYqqYkw1Vfr_y9aB"

#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define GAS_SENSOR_PIN 36  //GPIO36 SVP
#define DHT_PIN 32  //GPIO32 P32
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN 34 //GPIO34 P34

BlynkTimer timer;

//WIFI+Password
char ssid[] = "esuspenhereraika?";
char pass[] = "nongchoc3rd";

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  timer.setInterval(1000L, sendSensorData);
}

void sendSensorData() {

  //gas senser
  int gasValue = analogRead(GAS_SENSOR_PIN);
  gasValue = map(gasValue, 0, 4095, 0, 100);

  Blynk.virtualWrite(V0, gasValue);

  Serial.print("GasValue : ");
  Serial.print(gasValue);
  Serial.println("%");

 //DHT11
  float dhtTemp = dht.readTemperature(); 
  float dhtHum = dht.readHumidity();     

  if (isnan(dhtTemp) || isnan(dhtHum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, dhtTemp);
  Blynk.virtualWrite(V2, dhtHum);

  Serial.print("%, Temp (DHT): ");
  Serial.print(dhtTemp);
  Serial.print("°C, Humidity (DHT): ");
  Serial.println(dhtHum);

  //soilmoisturevalue
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  soilMoistureValue = map(soilMoistureValue, 0, 4095, 0, 100);

  Blynk.virtualWrite(V3, soilMoistureValue);

  Serial.print("Soil Moisture: ");
  Serial.print(soilMoistureValue);
  Serial.println("%");
}

void loop() {
  Blynk.run();  
  timer.run();  
}
