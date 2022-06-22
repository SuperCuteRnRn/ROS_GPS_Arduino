#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8,7);

const byte address1[6] = "00001";
const byte address2[6] = "0000A";

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1,address1);
  radio.openWritingPipe(address2);
  Serial.begin(115200);
  
  // put your setup code here, to run once:

}

void loop() {
  radio.startListening();
  if(radio.available())
  {
    char text_r[4];
    radio.read(&text_r, sizeof(text_r));
    Serial.println(text_r);

    radio.stopListening();
    char text_s[4] = "456";
    radio.write(&text_s,sizeof(text_s));

    
  }
}
