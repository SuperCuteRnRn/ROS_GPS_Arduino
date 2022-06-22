
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RX 6
#define TX 5
#define GPSBAUD 9600

TinyGPS gps;
SoftwareSerial uart_gps(RX, TX);
RF24 radio(7,8);
void getgps(TinyGPS &gps);

const byte address1[6] = "00001";
const byte address2[6] = "0000A";
float latitude, longitude;
char x;

void setup() {
  Serial.begin(9600);
  uart_gps.begin(GPSBAUD);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1,address1);
  radio.openWritingPipe(address2);
  
  // put your setup code here, to run once:

}

void loop() {
  radio.startListening();
  if(radio.available()){
    while(uart_gps.available()){
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c))      // if there is a new valid sentence...
      {
        gps.f_get_position(&latitude, &longitude);
        x=Serial.println(latitude,5);
        char text_r[4];
        radio.read(&text_r, sizeof(text_r));
        radio.stopListening();
        radio.write(&x, sizeof(x));
      }
    }
  }
}
