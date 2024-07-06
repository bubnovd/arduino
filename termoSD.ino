#include <SD.h>
#include <Wire.h>
#include <DS3231.h>

const int CS = 8;
const int TEMP = 0;
// const int SDA = A4;
// const int SCL = A5;
int val = 0;
float voltage, degreesC;

RTClib myRTC;
DS3231 rtc;

String year, month, day, hour, minute, second, date, stime;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!SD.begin(CS)){
    Serial.println("Card Failure");
    return;
  } else {
    Serial.print("Card ready");
  }
}

void loop() {
  File dataFile = SD.open("log.csv", FILE_WRITE);
  DateTime now = myRTC.now();
  val = analogRead(TEMP);
  // Correct to external power
  val -= 50;
  voltage = val * 0.004882814;
  degreesC = (voltage - 0.5) * 100.0;

  Serial.print("val: ");
  Serial.print(val);
  Serial.print(", voltage: ");
  Serial.print(voltage);
  Serial.print(", degreesC: ");
  Serial.println(degreesC);
  Serial.println(hour);
  Serial.println(minute);
  year = String(now.year(), DEC);
  month = String(now.month(), DEC);
  day = String(now.day(), DEC);
  hour = String(now.hour(), DEC);
  minute = String(now.minute(), DEC);
  second = String(now.second(), DEC);
  date = year + "/" + month + "/" + day;
  stime = hour + ":" + minute + ":" + second;
  if (dataFile){
    dataFile.print(date);
    dataFile.print(",");
    dataFile.print(stime);
    dataFile.print(",");
    dataFile.print(degreesC);
    dataFile.print(",");
    dataFile.print(val);
    dataFile.print(",");
    dataFile.println(voltage);
    dataFile.close();
  } else {
    Serial.println("Couldn't open log file");
  }
  delay(600000);

}
