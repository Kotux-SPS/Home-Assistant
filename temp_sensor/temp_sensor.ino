#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <esp_sleep.h>
#define MQTT_USER ""//your username for HA account
#define MQTT_PASSWORD ""//your password for HA account

// ---- WiFi settings ----1
#define WIFI_SSID ""//your ssid
#define WIFI_PASSWORD ""//your password

// ---- MQTT settings----
const char* mqtt_server = ""; // IP adress of your broker
WiFiClient espClient;
PubSubClient client(espClient);

// ---- Dallas DS18B20 ----
#define ONE_WIRE_BUS 4 //(you can change this for your board)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---- MQTT Discovery ----
const char* discoveryTopic = "homeassistant/sensor/dallas18b20/config";
const char* discoveryPayload = 
  "{\"name\":\"Dallas 18B20\","
  "\"uniq_id\":\"dallas18b20_01\","
  "\"stat_t\":\"dallas18b20/state\","
  "\"unit_of_meas\":\"°C\","
  "\"dev_cla\":\"temperature\","
  "\"val_tpl\":\"{{ value_json.temperature }}\"}";



void setup_wifi() {
  delay(10);
  Serial.println(WiFi.scanNetworks());
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  Serial.println("\nWiFi connected.");
  
}

void reconnect_mqtt() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      client.publish(discoveryTopic, discoveryPayload, true);

    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds...");
      delay(5000);
    }
  }
}
      
void setup() {
  Serial.begin(9600);
  sensors.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode (8,OUTPUT);
  pinMode(10,INPUT_PULLUP);
  WiFi.setSleep(false);
  
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  int tamper = digitalRead(10);
  Serial.print(tamper);

  // JSON message with state
  String payload = "{\"temperature\":";
  payload += tempC;
  payload += "}";

  client.publish("dallas18b20/state", payload.c_str(), true);
 

  if ((tempC>= 28)){
    digitalWrite(3,HIGH);
    client.publish("dallas18b20/alarm/temp","1",false);
  }
  else{
    digitalWrite(3,LOW);
     }
    if ((tamper==1)){
      digitalWrite(3,HIGH);
      client.publish("dallas18b20/alarm/tamper","1",false);
    }else{
      digitalWrite(3,LOW);
  }
delay(1000);
}
