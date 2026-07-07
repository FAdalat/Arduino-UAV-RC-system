#include <SPI.h>
#include <RF24.h>

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
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {

  if(radio.available()){
    radio.read(&data, sizeof(data));

    Serial.print("X1: ");
    Serial.print(data.x1);

    Serial.print(" Y1: ");
    Serial.print(data.y1);

    Serial.print(" X2: ");
    Serial.print(data.x2);

    Serial.print(" Y2: ");
    Serial.println(data.y2);
  }
}