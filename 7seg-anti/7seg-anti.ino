const int SER=5; // DATA 14
const int LATCH=6; // RCLK 12
const int CLK=7; // SRCLK 11
int CA_1 = 4;
int CA_2 = 3;

int seq[10] = {0b01000000, 0b01111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000};

/*
4021BS
0 abcdef  012345  0b01000000
1 bc      12      0b01111001
2 abged   01643   0b00100100
3 abcdg   01236   0b00110000
4 fgbc    5612    0b00011001
5 afgcd   05623   0b00010010
6 afgcde  056234  0b00000010
7 abc     012     0b01111000
8 abcdefg 0123456 0b00000000
9 abcdfg  012356  0b00010000
*/

void setup() {
  Serial.begin(9600);
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(CA_1, OUTPUT);
  pinMode(CA_2, OUTPUT);
}

void loop() {
  for (int i=0; i<10; i++)
  {  
    Serial.print("NUM= ");
    Serial.println(i);
    digitalWrite(CA_2, HIGH);
    digitalWrite(LATCH, LOW);
    shiftOut(SER, CLK, MSBFIRST, seq[i]);
    digitalWrite(LATCH, HIGH);
    delay(1000);
  }
}
