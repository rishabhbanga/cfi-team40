#include"AirQuality.h"
#include"Arduino.h"
AirQuality airqualitysensor;
int current_quality =3;
void setup()
{
    Serial.begin(9600);
}
void loop()
{
   
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

