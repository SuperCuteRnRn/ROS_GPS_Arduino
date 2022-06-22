#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8);

const byte address1[6] = "00001";
const byte address2[6] = "0000A";

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address1);
  radio.openReadingPipe(1,address2);
  Serial.begin(115200);
  
  // put your setup code here, to run once:

}

void loop() {
  radio.stopListening();
  char text_s[4] = "123";
  radio.write(&text_s, sizeof(text_s));

  radio.startListening();
  if(0>radio.available());
  char text_r[4];
  radio.read(&text_r,sizeof(text_r));
  Serial.println(text_r);
  delay(100);
  // put your main code here, to run repeatedly:

}
