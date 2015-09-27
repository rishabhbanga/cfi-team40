#include"AirQuality.h"
#include <Wire.h>
#include "rgb_lcd.h"
const int pinTemp = A0;   
rgb_lcd lcd;
int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
AirQuality airqualitysensor;
int current_quality =3; 
// Assigning initial color that'll be seen once the Galileo boots
int colorR = 255;
int colorG = 255;
int colorB = 0;
const int b=3975;
float resistance;
float temperature;
float humidity;               
 
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
    lcd.clear();
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
      // display color blue
      colorR = 0;
      colorG = 0;
      colorB = 255;
      lcd.setRGB(colorR, colorG, colorB);
      //display temperature
      lcd.print("It's cool at: ");
      lcd.print(temperature);
      lcd.setCursor (0 ,1);
      //display humidity
      Serial.print("Humidity is:  ");
      Serial.print(humidity);
      Serial.print("%");
      Serial.print("\t");
      lcd.setCursor (0 ,1);
      
      //display Dust Concentration
      ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
      concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
      Serial.print("Concentration of dust is: ");
      Serial.print(concentration);
      lcd.setCursor (0 ,1);
      Serial.print(" pcs/0.01cf  -  ");ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
      
      if (concentration < 1.0) 
      {
       Serial.println("It's a smokeless and dustless environment"); 
       }
      
     if (concentration > 1.0 && concentration < 20000)
     {
      Serial.println("It's probably only you blowing air to the sensor :)"); 
     }
    
    if (concentration > 20000 && concentration < 315000) 
     {
      Serial.println("Smokes from matches detected!"); 
     }
      if (concentration > 315000) 
     {
     Serial.println("Smokes from cigarettes detected! Or It might be a huge fire! Beware!"); 
     }
    
    lowpulseoccupancy = 0;
    starttime = millis();
    lcd.setCursor (0 ,1); 
    Serial.print("\n");
    
     if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality==0)
            Serial.println("High pollution! Force signal active");
        else if (current_quality==1)
            Serial.println("High pollution!");
        else if (current_quality==2)
            Serial.println("Low pollution!");
        else if (current_quality ==3)
            Serial.println("Fresh air");
    }
    Serial.print("\n");
    }
   
    else
    {
    	//display color red	
		  colorR = 255;
                  colorG = 0;
                  colorB = 0;
                  lcd.setRGB(colorR, colorG, colorB);
      //display temperature
      lcd.print("It's warm at: ");
      lcd.print(temperature);
      lcd.setCursor (0 ,1);
      //display humidity
     Serial.print("Humidity is:  ");
      Serial.print(humidity);
      Serial.print("%");
      Serial.print("\t");
      lcd.setCursor (0 ,1);
      
      //display Dust Concentration
      ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
      concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
      Serial.print("Concentration of dust is: ");
      Serial.print(concentration);
      lcd.setCursor (0 ,1);
      Serial.print(" pcs/0.01cf  -  ");ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
      if (concentration < 1.0) 
      {
        Serial.println("It's a smokeless and dustless environment"); 
      }
      
      if (concentration > 1.0 && concentration < 20000) 
      {
        Serial.println("It's probably only you blowing air to the sensor :)"); 
      }
    
    if (concentration > 20000 && concentration < 315000) 
    {
       Serial.println("Smokes from matches detected!"); 
    }
      if (concentration > 315000) 
    {
       Serial.println("Smokes from cigarettes detected! Or It might be a huge fire! Beware!"); 
    }
    
    lowpulseoccupancy = 0;
    starttime = millis();
    lcd.setCursor (0 ,1);     
     if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality==0)
            Serial.println("High pollution! Force signal active");
        else if (current_quality==1)
            Serial.println("High pollution!");
        else if (current_quality==2)
            Serial.println("Low pollution!");
        else if (current_quality ==3)
            Serial.println("Fresh air");
    }  
}
    
    delay(5000);         
    //display current temperature every reading 5 seconds
}
