/* Grove - Light Sensor demo v1.0
* 
* Signal wire to A0.
* By: http://www.seeedstudio.com
*/
#include <math.h>

#define LIGHT_SENSOR A0//Grove - Light Sensor is connected to A0 of Arduino
const int ledPin=12;                 //Connect the LED Grove module to Pin12, Digital 12
const int thresholdvalue=10;         //The treshold for which the LED should turn on. Setting it lower will make it go on at more light, higher for more darkness
float Rsensor; //Resistance of sensor in K
void setup() 
{
    Serial.begin(9600);                //Start the Serial connection
    pinMode(ledPin,OUTPUT);            //Set the LED on Digital 12 as an OUTPUT
}
void loop() 
{
    int sensorValue = analogRead(LIGHT_SENSOR); 
    Rsensor = (float)(4095-sensorValue)*10/sensorValue;
    Serial.println("the analog read data is ");
    Serial.println(sensorValue);
    Serial.println("the sensor resistance is ");
    Serial.println(Rsensor,DEC);//show the ligth intensity on the serial monitor;
}
