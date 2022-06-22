#include<ros.h>
#include<std_msgs/String.h>
#include<SoftwareSerial.h>
#include<TinyGPS.h>
#define RX 6
#define TX 5
#define GPSBAUD 9600

TinyGPS gps;
SoftwareSerial uart_gps(RX,TX);

ros::NodeHandle nh;
std_msgs::String str_msg;

ros::Publisher chatter("chatter", &str_msg);
char set = "watting for lock";

void getgps(TinyGPS &gps);

void setup() {
  nh.initNode();
  nh.advertise(chatter);
  Serial.begin(9600);
  uart_gps.begin(GPSBAUD);
}

/*void loop()
{
  str_msg.data = "watting";
  str_msg2.data = "for";
  
  chatter.publish( &str_msg );
  chatter.publish( &str_msg2 );
  nh.spinOnce();
}*/

void loop()
{
  
  float latitude, longitude;
  if(uart_gps.available())    // While there is data on the RX pin...
  {
    while(uart_gps.available()){
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c))      // if there is a new valid sentence...
      {
        getgps(gps);
        str_msg.data = "x";
        chatter.publish( &str_msg);
      }   
  }
  }else{
    str_msg.data = "watting";
    chatter.publish( &str_msg );
  }
  nh.spinOnce(); 
}


void getgps(TinyGPS &gps)
{
  float latitude, longitude;
  gps.f_get_position(&latitude, &longitude);
  Serial.print("Lat/Long: "); 
  Serial.print(latitude,5); 
  Serial.print(", "); 
  Serial.println(longitude,5);
  
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  Serial.print("Date: "); Serial.print(month, DEC); Serial.print("/"); 
  Serial.print(day, DEC); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(hour, DEC); Serial.print(":"); 
  Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC); 
  Serial.print("."); Serial.println(hundredths, DEC);
  
  Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());
  Serial.print("Course (degrees): "); Serial.println(gps.f_course());
  Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
  Serial.println();
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
  delay(10000);
}
