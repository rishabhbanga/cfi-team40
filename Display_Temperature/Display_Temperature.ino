
//Check and display temperature 
#include <Wire.h>
#include "rgb_lcd.h"
const int pinTemp = A0;    
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 255;
const int colorB = 0;
const int b=3975; 
float resistance;
float temperature;
float humidity;
int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
                


void setup()
{
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    delay(1000);
    Serial.begin(9600);
    pinMode(8,INPUT);
    starttime = millis();//get the current time;

}

void loop()
{
    delay(1000);
    int val = analogRead(pinTemp);                              
    resistance=(float)(1023-val)*10000/val;  
     //calculate the temperature    
    temperature=1/(log(resistance/10000)/b+1/298.15)-273.15-30;     
    humidity=1/(log(resistance/10000)/b+1/298.15)-273.15-37;
     duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
   
    if (temperature < 25)
    {    
      const int colorR = 0;
      const int colorG = 0;
      const int colorB = 255;
      lcd.setRGB(colorR, colorG, colorB);
      //display temperature
      lcd.print("It's cool at: ");
      lcd.print(temperature);
      lcd.setCursor (0 ,1);   //Reset cursor to start of line
      lcd.print("Humidity is: ");
      lcd.print(humidity);
      lcd.setCursor (0 ,1);   //Reset cursor to start of line
        if (concentration < 1.0) {
    lcd.print("It's a smokeless and dustless environment"); 
     lcd.setCursor (0 ,1);  
}
    if (concentration > 1.0 && concentration < 20000) {
     lcd.print("It's probably only you blowing air to the sensor :)"); 
      lcd.setCursor (0 ,1);  
  }
    
    if (concentration > 20000 && concentration < 315000) {
     Serial.println("Smokes from matches detected!"); 
    }
      if (concentration > 315000) {
     Serial.println("Smokes from cigarettes detected! Or It might be a huge fire! Beware!"); 
  }
    
    lowpulseoccupancy = 0;
    starttime = millis();
     }
    
    else
    {
      const int colorR = 255;
      const int colorG = 0;
      const int colorB = 0;
      lcd.setRGB(colorR, colorG, colorB);      
      //display temperature
      lcd.print("It's warm at: ");
      lcd.print(temperature);
      lcd.setCursor (0 ,1);   //Reset cursor to start of line
      lcd.print("Humidity is");
      lcd.print(humidity);
      lcd.setCursor (0 ,1);   //Reset cursor to start of line
    }
     
    delay(5000);          
    //display current temperature every reading 5 seconds
}

