const int SER=5; // DATA 14
const int LATCH=6; // RCLK 12
const int CLK=7; // SRCLK 11

int seq[14] = {1,3,7,15,31,63,127,255,64,32,16,8,4,2};

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLK, MSBFIRST, B10101010);
  digitalWrite(LATCH, HIGH);
}

void loop() {
  for (int i=0; i<14; i++)
  {
    digitalWrite(LATCH, LOW);
    shiftOut(SER, CLK, MSBFIRST, seq[i]);
    digitalWrite(LATCH, HIGH);
    delay(300);
  }
}
