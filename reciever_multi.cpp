
#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
//#include<bits/stdc++.h>

 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 char msg[] = "" ;
 char check_1[] = "1";
 char check_2[] = "2";
 char* p1;
 char* p2;
 int counter1 = 0;
 int counter2 = 0;
 int last_time;
void setup()
{
// Initialize ASK Object
  rf_driver.init();
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
// Setup Serial Monitor
  Serial.begin(9600);
}
 
void loop()
{
// Set buffer to size of expected message
  uint8_t buf[8];
  uint8_t buflen = sizeof(buf);
  //Serial.println(buflen);
// Check if received packet is correct size
 if (rf_driver.recv(buf, &buflen))
 {
    last_time = millis();
    Serial.println(last_time);
    p1 = strstr((char*)buf,check_1);
    if(p1){
      Serial.println("Found Device 1");
      digitalWrite(2,HIGH);
      counter1 = 0;
    }
    else{
      Serial.println("Not Found");
      counter1++;
      if(counter1 >= 2){
        digitalWrite(2,LOW);
        //counter1 = 0;
      }
    }
    
      p2 = strstr((char*)buf,check_2);
     // Serial.println(*p2);
    if(p2){
      Serial.println("Found Device 2");
      digitalWrite(3,HIGH);
      counter2 = 0;
    }
    else{
      Serial.println("Not Found");
      counter2++;
      if(counter2 >= 2){
        digitalWrite(3,LOW);
      }
    }
      
    Serial.print("Message Received: ");
    Serial.println((char*)buf);
  }

  else{
    if(millis() - last_time > 3000){
      // Serial.println("yes im in");
      digitalWrite(2,LOW);
      digitalWrite(3,LOW); 
    }
  }
}
