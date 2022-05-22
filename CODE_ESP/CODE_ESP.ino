#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLbYbsdmDU"
#define BLYNK_DEVICE_NAME "DHT11"
#define RX D1 
#define TX D2


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<SoftwareSerial.h>


SoftwareSerial mySerial(RX,TX);

char auth[] = "oll0lbcE4Ty8rqtNY_BA5D5uawAxsdPC";
char ssid[] = "NHIN LAM GI";
char pass[] = "0384300646t$";

int Button1 ;
int Button2 ;
int Button3 ;
int timer1 ;
int timer2 ;
String Trans_Data ;
String Re_Data ;
String Value_re1 ;
String Value_re2 ;
String Value_re3 ;
String Value_re4 ;

void setup() {
  // put your setup code here, to run once:
   Blynk.begin(auth, ssid, pass);
   Serial.begin(9600);
   mySerial.begin(9600);
   timer1 = millis();
   timer2 = millis();
}
BLYNK_WRITE(V4){
  int pinLED = param.asInt();
  if(pinLED){
    Button1 = 1 ;
  }else{
    Button1 = 0 ;
  }
}
BLYNK_WRITE(V5){
  int pinDC = param.asInt();
   if(pinDC){
    Button2 = 1 ;
  }else{
    Button2 = 0 ;
  }
}
BLYNK_WRITE(V6){
  int pinBOM = param.asInt();
   if(pinBOM){
     Button3 = 1 ;
  }else{
     Button3 = 0 ;
  }
}
void loop() {
   if(millis() - timer1 > 500){
      Trans_Data = "a"+String(Button1)+"b"+String(Button2)+"c"+String(Button3)+"f" ;
      mySerial.println(Trans_Data);
      timer1 = millis();
   }
   Receive_data();
   if(millis() - timer2 > 1000){
      Trans_blynk();
      timer2 = millis();
   }
   Serial.print(Value_re1);
   Serial.print(" | ");
   Serial.print(Value_re2);
   Serial.print(" | ");
   Serial.print(Value_re3);
   Serial.print(" | ");
   Serial.println(Value_re4);
   Trans_Data="";
   Blynk.run();
   delay(100);
}
/*------------------------------------------------------------------------------*/
void Trans_blynk(){
   Blynk.virtualWrite(V1,Value_re2.toInt());
   Blynk.virtualWrite(V0, Value_re1.toInt());
   Blynk.virtualWrite(V2, Value_re4.toInt());
   Blynk.virtualWrite(V3, Value_re3.toInt());
} 
void Receive_data(){
     while(mySerial.available()>0){
      char C = (char)mySerial.read();
      Re_Data += C ;
        if(C == 'a'){
       Re_Data = ""; 
       }else if(C == 'b'){
       Value_re1= Re_Data.substring(0,Re_Data.indexOf('b'));
       Re_Data = "";
     }else if (C == 'c'){
       Value_re2= Re_Data.substring(0,Re_Data.indexOf('c'));
       Re_Data= "";
     }else if (C == 'd'){
       Value_re3= Re_Data.substring(0,Re_Data.indexOf('d'));
       Re_Data = "";
     }else if(C == 'f') {
       Value_re4= Re_Data.substring(0,Re_Data.indexOf('f'));
       Re_Data = "";
    }
    }
}
