#define BLYNK_TEMPLATE_ID "TMPL4********"
#define BLYNK_TEMPLATE_NAME "Light"
#define BLYNK_AUTH_TOKEN "6uI*************"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#define button1_pin 26
#define relay1_pin 13
int relay1_state = 0;
#define button1_vpin    V3
#define DHTPIN 4
#define LED 14
#define DHTTYPE DHT11
BlynkTimer timer;

DHT dht (DHTPIN, DHTTYPE);
// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Your_Name_Wifi";
char pass[] = "Password_WIFI";
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
}
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}
void setup()
{

  // Debug console
  Serial.begin(115200);
   pinMode(button1_pin, INPUT_PULLUP);
   pinMode(relay1_pin, OUTPUT);
   digitalWrite(relay1_pin, HIGH);
  pinMode(LED, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
 

  digitalWrite(LED, 1);
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("Temp: "); 
  Serial.print(temp);
  Serial.print(" C ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" % ");
  
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, humidity);
  delay(5000);
  Blynk.run();
   timer.run();
     listen_push_buttons();

 
}
void listen_push_buttons(){
    //--------------------------------------------------------------------------
    if(digitalRead(button1_pin) == LOW){
      delay(200);
      control_relay(1);
      Blynk.virtualWrite(button1_vpin, relay1_state); //update button state
    }
}
void control_relay(int relay){
  //------------------------------------------------
  if(relay == 1){
    relay1_state = !relay1_state;
    digitalWrite(relay1_pin, relay1_state);
    Serial.print("Relay1 State = ");
    Serial.println(relay1_state);
    delay(50);
  }
}
