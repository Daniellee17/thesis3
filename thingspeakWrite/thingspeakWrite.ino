#include <ThingSpeak.h>
#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(7, 8);

#include <String.h>

// ThingSpeak information
char* server = "api.thingspeak.com";
unsigned long channelID = 742592;
char* readAPIKey = "3QTHZH1C59VFPVEO";
unsigned int dataFieldOne = 1;   

void setup()
{
  gprsSerial.begin(9600);               // the GPRS baud rate
  Serial.begin(9600);    // the GPRS baud rate

  delay(1000);
}

void loop()
{
  float h = 1.0;
  float t = 2.0;
  delay(100);

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" %");

  ConnectGPRS();

  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);

  ShowSerialData();

  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();

  String str = "GET https://api.thingspeak.com/update?api_key=2LPC7FECP9PL1KPT&field1=" + String(t) + "&field2=" + String(h);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server

  delay(4000);
  ShowSerialData();

  gprsSerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet
  gprsSerial.println();

  ShowSerialData();

  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}
void ShowSerialData()
{
  while (gprsSerial.available() != 0)
    Serial.write(gprsSerial.read());
  delay(5000);

}

void ConnectGPRS()
{
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());

  gprsSerial.println("AT");
  delay(1000);

  gprsSerial.println("AT+CPIN?");
  delay(1000);

  gprsSerial.println("AT+CREG?");
  delay(1000);

  gprsSerial.println("AT+CGATT?");
  delay(1000);

  gprsSerial.println("AT+CIPSHUT");
  delay(1000);

  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);

  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);

  ShowSerialData();

  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);

  ShowSerialData();

  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);

  ShowSerialData();

  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(2000);

  ShowSerialData();

  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);

  ShowSerialData();

}
