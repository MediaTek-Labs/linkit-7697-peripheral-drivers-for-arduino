#include <Wire.h>
#include "I2Cdev.h"
#include <MPU9250.h>

class MPU9250Block
{
  public:
    // must call this in setup()
    void begin();

    // X-axis acceleration, unit is G.
    double getAccX();

    // Y-axis acceleration, unit is G.
    double getAccY();

    // Z-axis acceleration, unit is G.
    double getAccZ();

    double getGyroX();

    double getGyroY();

    double getGyroZ();

    double getMagX();

    double getMagY();

    double getMagZ();

    double getPitch();

    double getRoll();

    double getYaw();

    double getDegreeToMagNorth();

  protected:
    void readMagData();

    static double convertAcc(int16_t acc);
    static double convertGyro(int16_t gyro);
    static double convertMag(int16_t mag);
};