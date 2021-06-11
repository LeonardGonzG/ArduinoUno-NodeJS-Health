#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"
#include <SoftwareSerial.h>

#define REPORTING_PERIOD_MS     300

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
PulseOximeter pox;
uint32_t tsLastReport = 0;

bool stateSend = false;

//Data send
float heart_rate = 0;
float oxygen_saturation = 0;
float temp_ambC = 0;
float temp_objC = 0;

int lightNum=9;
int statusPresent = 0;

void setup() {
     Serial.begin(2000000);
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);



    Serial.println("Adafruit MLX90614 test");  
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    mlx.begin();  
 

}

void loop() {

  pox.update();

   statusPresent = digitalRead(10);
    
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      
      heart_rate = pox.getHeartRate();
      oxygen_saturation = pox.getSpO2();
      temp_ambC = mlx.readAmbientTempC();
      temp_objC = mlx.readObjectTempC();
      tsLastReport = millis();
     
    }

   if (heart_rate > 0 and oxygen_saturation> 0 and statusPresent== HIGH){
      stateSend = true;
    }

    if(statusPresent == LOW){
      digitalWrite(11, LOW);
    }else{
        digitalWrite(11, HIGH);
    }
    
    if(stateSend){
        showDataSend();
        animationLeds();
      }
      
      heart_rate = -1;
      oxygen_saturation = -1;
      stateSend = false;
 
}

void animationLeds(){
  
    if(lightNum<5){
      for(int i =9; i>=5; i--){
          digitalWrite(i, LOW);
          }
          lightNum=9;  
    }else{
       digitalWrite(lightNum, HIGH);
       lightNum--;
      }
    
   }



   

void showDataSend(){
 
    Serial.println(String(heart_rate)+
                ','+String(oxygen_saturation) + 
                ','+String(temp_ambC)+
                ','+String(temp_objC));
 /*
  //[heartRate, oxygen, tempAmbC, tempObjC]
  
 */  
}
