#include <Wire.h>
#include <mpu9250_blockly.h>

MPU9250Block mpu;

void setup()
{
    Serial.begin(9600);
    mpu.begin();
}

void loop()
{
    const double ax = mpu.getAccX();
    const double ay = mpu.getAccY();
    const double az = mpu.getAccZ();

    Serial.print("ax:");
    Serial.println(ax);
    Serial.print("ay:");
    Serial.println(ay);
    Serial.print("az:");
    Serial.println(az);
    
    const double gx = mpu.getGyroX();
    const double gy = mpu.getGyroY();
    const double gz = mpu.getGyroZ();
    Serial.print("gx:");
    Serial.println(gx);
    Serial.print("gy:");
    Serial.println(gy);
    Serial.print("gz:");
    Serial.println(gz);
    
    const double mx = mpu.getMagX();
    const double my = mpu.getMagY();
    const double mz = mpu.getMagZ();
    Serial.print("mx:");
    Serial.println(mx);
    Serial.print("my:");
    Serial.println(my);
    Serial.print("mz:");
    Serial.println(mz);

    const float heading = mpu.getDegreeToMagNorth();
    Serial.print("heading:");
    Serial.println(heading);


    const double pitch = mpu.getPitch();
    const double roll = mpu.getRoll();
    const double yaw = mpu.getYaw();
    Serial.print("pitch:");
    Serial.println(pitch);
    Serial.print("roll:");
    Serial.println(roll);
    Serial.print("yaw:");
    Serial.println(yaw);
    
    delay(1000);
}