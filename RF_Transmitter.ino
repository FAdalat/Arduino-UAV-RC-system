#include <SPI.h>
#include <RF24.h>

int x1pin = A3;
int y1pin = A5;
int x2pin = A7;
int y2pin = A6;

RF24 radio(9,10);
const byte address[6] = "xxxxx";

struct Data {
  int x1;
  int y1;
  int x2;
  int y2;
};

Data data;

void setup() {
  pinMode(x1pin, INPUT);
  pinMode(y1pin, INPUT);
  pinMode(x2pin, INPUT);
  pinMode(y2pin, INPUT);

  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {

  data.x1 = analogRead(x1pin);
  data.y1 = analogRead(y1pin);
  data.x2 = analogRead(x2pin);
  data.y2 = analogRead(y2pin);

  data.x1 = map(data.x1, 0, 1023, 0, 180);
  data.y1 = map(data.y1, 0, 1023, 0, 180);
  data.x2 = map(data.x2, 0, 1023, 0, 180);
  data.y2 = map(data.y2, 0, 1023, 0, 180);
  

  bool ok = radio.write(&data, sizeof(data));

  if(ok){
    Serial.println("Data sent");
  } else {
    Serial.println("Send failed");
  }

  delay(100);
}