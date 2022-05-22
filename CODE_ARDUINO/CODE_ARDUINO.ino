#include<SoftwareSerial.h>
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define DHT11Pin 2 
#define DHTType DHT11 
#define RX 8
#define TX 9
#define DC1 5
#define DC2 6
#define Relay 7 
#define Button1 10
LiquidCrystal_I2C lcd(0x27,16,2); 
DHT HT(DHT11Pin,DHTType);
SoftwareSerial mySerial(RX,TX);

int Val_Sensor1 ;
int Val_Sensor2 ;
int Val_Sensor3 ;
int Val_Sensor4 ;
int timer1 ;
int timer2 ;
int timer3 ;
int lastbutton = 0;
int button ;
int count ;
String Trans_Data ;
String Re_Data ;
String Value1 ;
String Value2 ;
String Value3 ;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    mySerial.begin(9600);
    lcd.init();                    
    lcd.backlight();
    HT.begin();
    pinMode(DC1 , OUTPUT);
    pinMode(DC2 , OUTPUT);
    pinMode(Relay , OUTPUT);
    pinMode(Button1 , INPUT);
}

void loop() {
  if(millis() - timer1 > 500){ 
     Read_data();
     Trans_Data = "a"+String(Val_Sensor1)+"b"+String(Val_Sensor2)+"c"+String(Val_Sensor3)+"d"+String(Val_Sensor4)+"f";
     mySerial.println(Trans_Data);
     timer1 = millis();
  }
  Receive_data();                                       
  Swich();
  LCD();
  Serial.print(Value1); 
  Serial.print(" | ");
  Serial.print(Value2);
  Serial.print(" | ");
  Serial.println(Value3); 
  Trans_Data ="";
  delay(100);
}
/* =================================================================================*/
void LCD(){
  button = digitalRead(Button1);
   if(button != lastbutton){
     if(button == HIGH){
      count++;
    }
   }
   lastbutton = button ;
     if(count%2==1){
      if(button == HIGH){
        if(millis()-timer3 >100){
        lcd.clear();
        timer3=millis();
        }
      }
  lcd.setCursor(0,0);
  lcd.print("Nhiet do:");
  lcd.setCursor(9,0);
  lcd.print(Val_Sensor2);
  lcd.setCursor(0,1);
  lcd.print("Do am:");
  lcd.setCursor(7,1);
  lcd.print(Val_Sensor1);    
   }else{
     if(button == HIGH){
      if(millis()-timer3 >100){
        lcd.clear();
         timer3=millis();
        }
      }
  lcd.setCursor(0,0);
  lcd.print("Do am dat:");
  lcd.setCursor(11,0);
  lcd.print(Val_Sensor4);
  lcd.setCursor(0,1);
  lcd.print("Anh sang:");
  lcd.setCursor(10,1);
  lcd.print(Val_Sensor3);  
   }
}
void Swich(){
  digitalWrite(DC1 , Value1.toInt());
  digitalWrite(DC2 , Value2.toInt());
  digitalWrite(Relay ,Value3.toInt());
}
void Read_data(){
   int tempF = HT.readTemperature(true);
   Val_Sensor1 = HT.readHumidity();   
   Val_Sensor2 = HT.readTemperature();
   Val_Sensor3 = analogRead(A0);
   Val_Sensor4 = analogRead(A1);
}
void Receive_data(){
      while(mySerial.available()>0){
        char C = (char)mySerial.read();
        Re_Data += C ;
        if(C == 'a'){
       Re_Data = ""; 
       }else if(C == 'b'){
       Value1= Re_Data.substring(0,Re_Data.indexOf('b'));
       Re_Data = "";
     }else if (C == 'c'){
       Value2= Re_Data.substring(0,Re_Data.indexOf('c'));
       Re_Data= "";
     }else if(C == 'f') {
       Value3= Re_Data.substring(0,Re_Data.indexOf('f'));
       Re_Data = "";
       }
    }
}
