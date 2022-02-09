const int AOUTpin=A2;
const int DOUTpin=12;
int esikDegeri;
int ppm;
int veriPini = A0; // Siyah kablonun (sensörün soldan 2. pini) bağlı olduğu pin
float toz=0; //Gelen veriyi sakladığımız değişken
int led=15; // Beyaz kablonun (sensörün soldan 3. pini) bağlı olduğu pin
#include <LiquidCrystal.h>
#include <virtuabotixRTC.h>
#include <SPI.h>
#include <SD.h>
#include <dht11.h> 
int DhtPin=2; 
dht11 dht_sensor;
File myFile;
const int chipSelect = 53;/*MOSI->51 MİSO->50  SCK->52  CS->53*/
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
virtuabotixRTC Saat(9,10,11); //CLK -> , Data ->10 , RST -> 
void setup() {
  lcd.begin(16,2);
Serial.begin(9600);
pinMode(DOUTpin, INPUT);
pinMode(led,OUTPUT);
pinMode(veriPini, INPUT);
}
void loop()
{
Saat.updateTime();
lcd.home();
lcd.print(Saat.hours);
lcd.print(".");

lcd.print(Saat.minutes);

lcd.setCursor(7,0);
int chk = dht_sensor.read(DhtPin);
lcd.print((float)dht_sensor.temperature, 2);
lcd.setCursor(0,1);
lcd.print("Gaz:");
ppm= analogRead(AOUTpin);
esikDegeri= digitalRead(DOUTpin);
Serial.print(" Hava kirliliği: ");
Serial.print(ppm);
Serial.print("ppm.");
if (esikDegeri == 1)
{
Serial.println("Hava Kirlilik değeri eşik değerinin altında");
lcd.setCursor(4,1);
lcd.print("YOK");
}
else
{
Serial.println("Hava Kirlilik değeri eşik değerinin üzerinde, ortamdan uzaklaşın.");
lcd.setCursor(4,1);
lcd.print("VAR");
 } 
 digitalWrite(led,LOW); 
delayMicroseconds(280);
toz=analogRead(veriPini); 
delayMicroseconds(40);
digitalWrite(led,HIGH); 
delayMicroseconds(9860);
delay(1000);
Serial.println(toz);
if (toz>36.455){
float kalite=(float(toz/1024)-0.0356)*120000*0.035;
Serial.println(kalite);
if (kalite>1000){
  lcd.setCursor(8,1);
  lcd.print("Tozlu");
  }
  else{
    lcd.setCursor(8,1);
    lcd.print("Normal");
    }
}}
