#include <Wire.h>
#include <adxl345_blockly.h>

ADXL345Block adxl;

void setup()
{
    Serial.begin(9600);
    adxl.begin();
}

void loop()
{
    const float x = adxl.getX();
    const float y = adxl.getY();
    const float z = adxl.getZ();
    const float pitch = adxl.getPitch();
    const float roll = adxl.getRoll();

    Serial.print("x:");
    Serial.println(x);
    Serial.print("y:");
    Serial.println(y);
    Serial.print("z:");
    Serial.println(z);
    Serial.print("pitch:");
    Serial.println(pitch);
    Serial.print("roll:");
    Serial.println(roll);

    delay(500);

    adxl.detectGesture();
    if (adxl.isActivityDetected())
    {
        Serial.println("*** ACTIVITY ***");
        //add code here to do when activity is sensed
    }

    // Double Tap Detection
    //interrupts = adxl.getInterruptSource();
    if (adxl.isDoubleTapDetected())
    {
        Serial.println("*** DOUBLE TAP ***");
        //add code here to do when a 2X tap is sensed
    }

    // Tap Detection
    // interrupts = adxl.getInterruptSource();
    if (adxl.isTapDetected())
    {
        Serial.println("*** TAP ***");
        //add code here to do when a tap is sensed
    }

    delay(500);
    
}