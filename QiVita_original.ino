  #include <Wire.h>
  #include <SoftwareSerial.h>

#define SLAVE_ADDRESS 0x04

int val;
int x;
int y;
int analog;
int result;
int sender = 5;
int pin,flag=0;
int k = 0;
char chislo;

void setup()
{
  
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT); 
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}
 
void loop()
{   
  
//  if(pin == 2) {
//   digitalWrite(7, HIGH);
//   delay(10000);
//   digitalWrite(7, LOW);
//  }
  if(flag==1)
  {
  
  val=analogRead(pin);
  x = analogRead(A1);
  y = analogRead(A2);
  analog = analogRead(A3);
  result = analog / (x / 24 + y / 24) * 14;

  for(int i = 0; i < 60; i++) {
    k = k + result;
    delay(1000);
    Serial.println(i);
  }
  sender = k / 300;
  sendData();
    
  if (sender >= 140 && sender <= 254) Serial.println("Гастрит");
  else if (sender >= 298 && sender <= 368) Serial.println("Повышенное давление");
  else if (sender >= 405 && sender <= 482) Serial.println("ВЧД");
  else if (sender >= 502 && sender <= 801) Serial.println("Пониженное давление");
  else if (sender >= 825 && sender <= 938) Serial.println("Панкреатит");
  else  Serial.println("Нет болезни");
  
  flag = 0;
  }
}
void receiveData(int byteCount)
{
    while(Wire.available()>0) 
    {
      pin=Wire.read();
      flag=1;
    }
}

void sendData()
{
  if(sender > 255 && sender < 512) chislo = 1;
  else if( sender > 511 && sender < 768) chislo = 2;
  else if(sender > 767) chislo = 3;
  Wire.write(sender);
  Wire.write(chislo); 
  
}   

