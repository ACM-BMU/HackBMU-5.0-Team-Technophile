#include <SoftwareSerial.h>
#include <Wire.h>
#include <TinyGPS++.h>
#define RX 2
#define TX 3
String AP = "Mi A3";       
String PASS = "10445@$rk"; 
String API = "1FQ5J6GLG3NEQV5J";   
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field3";
String field2 = "field2";
String field1 = "field1";
String field3 = "field4";
float countTrueCommand;
float countTimeCommand; 
boolean found = false; 
float valSensor = 1;
int ADXL345 = 0x53;

SoftwareSerial esp8266(RX,TX);// 2 3
SoftwareSerial serial_connection(5,6); //tx,rx for Neo_6m_gps_module
TinyGPSPlus gps; 
 
  
void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D); 
  
  Wire.write(8); 
  Wire.endTransmission();

  pinMode(13,OUTPUT);
  
  delay(10);
  
  serial_connection.begin(9600);     
  Serial.println("GPS Start"); 
     
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {
  valSensor = getSensorData(ADXL345);
  float longitude = 0;
  float latitude = 0;
  String Time="";
  getting_latitude_and_longitude(latitude, longitude, Time);
  
  if (valSensor>26.4){
   digitalWrite(13,HIGH);
  String getData = "GET /update?api_key="+ API +"&"+field1+"="+String(latitude)+"&"+field2+"="+String(longitude)+"&"+field +"="+String(valSensor)+"&"+field3+"="+String(Time);
  sendCommand("AT+CIPMUX=1",5,"OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
  sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
  esp8266.println(getData);delay(1500);countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0",5,"OK");
  }else{
    digitalWrite(13,LOW);
    Serial.println("g_force valus is lower than 25g");
  }
}

int getSensorData(int ADXL345){
  int led_pin=13;
  float X_out, Y_out, Z_out;
  float g_force;
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  X_out = ( Wire.read() | Wire.read() << 8);
  Y_out = ( Wire.read() | Wire.read() << 8);
  Z_out = ( Wire.read() | Wire.read() << 8);
  Serial.print("g-Xaxis: ");
  Serial.print(X_out);
  Serial.print(" ");
  Serial.print("g-Yaxis: ");
  Serial.print(Y_out);
  Serial.print(" ");
  Serial.print("g-Zaxis: ");
  Serial.print(Z_out);
  g_force=pow(X_out,2)+pow(Y_out,2)+pow(Z_out,2);
  float g_square=pow(9.8,2);
  g_force=sqrt(g_force/g_square);
  Serial.println(" ");
  Serial.print("g-force: ");
  Serial.print(g_force);
  Serial.println("g");
  return g_force; 
}

int getting_latitude_and_longitude(float &latitude, float &longitude, String &Time){
  Time="";
  while(serial_connection.available())             
  {
    gps.encode(serial_connection.read());           
  }
  if(gps.location.isUpdated())          
  {
    
    Serial.print("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    latitude=gps.location.lat();
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    longitude=gps.location.lng();
    Serial.println(gps.location.lng(), 6);
    
    Serial.print("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");

    Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  
  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Time=Time+gps.time.hour();
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Time=Time+gps.time.minute();
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Time=Time+gps.time.second();
    Serial.print(gps.time.second());
    Serial.print(".GMT");
  }
  Serial.println("");
  delay(2000);
  }
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);
    if(esp8266.find(readReplay))
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("CONNECTED");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("FAILED TO CONNECTED");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
