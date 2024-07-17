#include <DHT11.h>
DHT11 dht11(2);

const int SER=5; // DATA 14
const int LATCH=6; // RCLK 12
const int CLK=7; // SRCLK 11
int CA_1 = 3;
int CA_2 = 4;

int CAS[2] = {CA_1, CA_2};
int digits[2];

int number = 0;
int first_digit = 0;
int second_digit = 0;

int seq[10] = {0b01000000, 0b01111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000};

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(CA_1, OUTPUT);
  pinMode(CA_2, OUTPUT);
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  break_number(temperature);
  display_number();
}

void break_number(int num) {
  first_digit = num / 10;
  digits[0] = first_digit;

  second_digit = num - (first_digit * 10);
  digits[1] = second_digit;
}

void display_number() {
  for (int i=0; i<2; i++){
    digitalWrite(CA_1, HIGH);
    digitalWrite(CA_2, HIGH);
    digitalWrite(CAS[i], LOW);
    digitalWrite(LATCH, LOW);    
    shiftOut(SER, CLK, MSBFIRST, seq[digits[i]]);
    //digitalWrite(CAS[i], HIGH); //налдо хвй
    // или мб дело в анодах-катодах
    digitalWrite(LATCH, HIGH);
    delay(5);
  }
}