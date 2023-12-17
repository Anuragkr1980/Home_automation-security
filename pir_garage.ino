#define BLYNK_TEMPLATE_ID "TMPL3tCU8vmhH"
#define BLYNK_TEMPLATE_NAME "motion sensor"
#define BLYNK_AUTH_TOKEN "SzxYc2Uk3oIw-V24cdyZleCbi_qzufIE"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <WiFiClient.h>
#include "BlynkEdgent.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi 10";    //ssid or hotspot name
char pass[] = "012345687";       // password




int LED_buzzer = 14;          //pin D5
const int SENSOR_1 = 16;      //pin D0
const int SENSOR_2 = 5;       //pin D1
const int SENSOR_3 = 0;       //pin D3
const int LDRSensor_1 = 12;   //pin D6
const int LDRSensor_2 = 13;   //pin D7
const int relaypin1 = 2;      //pin D4
const int relaypin2 = 15;     //pin D8

#define VPIN_BUTTON_1 V5
#define VPIN_BUTTON_2 V6

bool toggleState_1 = LOW;
bool toggleState_2 = LOW;

Servo myservo;     //define servo name

BlynkTimer timer;


BLYNK_CONNECTED(){
  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);

}


BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  if(toggleState_1 == 1){
    digitalWrite(relaypin1, LOW);
  }
  else { 
    digitalWrite(relaypin1, HIGH);
  }
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  if(toggleState_2 == 1){
    digitalWrite(relaypin2, LOW);
  }
  else { 
    digitalWrite(relaypin2, HIGH);
  }
}




BLYNK_WRITE(V1)
{   
  int pos = param.asInt(); // Get value as integer
  myservo.write(pos);
}



void setup() {

  pinMode(LED_buzzer, OUTPUT); 
  pinMode(SENSOR_1, INPUT); 
  pinMode (LDRSensor_1, INPUT);
  pinMode (LDRSensor_2, INPUT);
  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);


  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  myservo.attach(4);    //pin D2
  
  analogWrite(LED_buzzer, 0); 
  digitalWrite(relaypin1, HIGH);
  digitalWrite(relaypin2, HIGH);


  BlynkEdgent.begin();
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);


}

void loop() {
  Blynk.run();
  timer.run();
  BlynkEdgent.run();

   int sensorvalue1 = digitalRead(SENSOR_1);    
   int sensorvalue2 = digitalRead(SENSOR_2);
   int sensorvalue3 = digitalRead(SENSOR_3);
   

  Serial.print(sensorvalue1);
  Serial.println(sensorvalue2);
  Serial.println(sensorvalue3);

   int Sensordata_1 = digitalRead (LDRSensor_1);
   int Sensordata_2 = digitalRead (LDRSensor_2);
  
  if (sensorvalue1== 1 ) 
  {
    Blynk.virtualWrite(V2, sensorvalue1);
   analogWrite(LED_buzzer, 255);
    delay(100);
    }

  else if (sensorvalue2== 1 ) 
  {
    Blynk.virtualWrite(V3, sensorvalue2);
   analogWrite(LED_buzzer, 255);
    delay(100);
    }

   else if (sensorvalue3== 1 ) 
  {
    Blynk.virtualWrite(V4, sensorvalue3);
   analogWrite(LED_buzzer, 255);
    delay(100);
    }
  else {
    analogWrite(LED_buzzer, 0);
   }




if(Sensordata_1==1 )
{
  analogWrite(LED_buzzer, 255);
  Serial.print("Sensor value:");
  Serial.println(Sensordata_1);
  delay(100);
}
else if(Sensordata_2==1 )
{
  analogWrite(LED_buzzer, 255);
  Serial.print("Sensor value:");
  Serial.println(Sensordata_1);
  delay(100);
}
else{
  analogWrite(LED_buzzer, 0);
}

  
}
