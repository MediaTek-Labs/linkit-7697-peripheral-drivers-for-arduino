#include <mpu9250_blockly.h>

static MPU9250 accelgyro;
static I2Cdev I2C_M;

static int16_t mx;
static int16_t my;
static int16_t mz;

static uint8_t buffer_m[6] = {0};

void MPU9250Block::begin()
{
    Wire.begin();
    accelgyro.initialize();
    
    mx = 0;
    my = 0;
    mz = 0;

    Serial.println(accelgyro.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");

    delay(1000);
}

void MPU9250Block::readMagData()
{
    //read mag
	I2Cdev::writeByte(MPU9250_DEFAULT_ADDRESS, MPU9250_RA_INT_PIN_CFG, 0x02); //set i2c bypass enable pin to true to access magnetometer
	delay(10);
	I2Cdev::writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01); //enable the magnetometer
	delay(10);
	I2Cdev::readBytes(MPU9150_RA_MAG_ADDRESS, MPU9150_RA_MAG_XOUT_L, 6, buffer_m);
	mx = (((int16_t)buffer_m[1]) << 8) | buffer_m[0];
    my = (((int16_t)buffer_m[3]) << 8) | buffer_m[2];
    mz = (((int16_t)buffer_m[5]) << 8) | buffer_m[4];	
}

double MPU9250Block::convertAcc(int16_t acc)
{
    return (double)acc / 16384.0;
}

double MPU9250Block::convertGyro(int16_t gyro)
{
    return (double)gyro * 250.0 / 32768.0;
}

double MPU9250Block::convertMag(int16_t mag)
{
    return (double)mag * 4800.0 / 8192.0;
}

// X-axis acceleration, unit is G.
double MPU9250Block::getAccX()
{
    return convertAcc(accelgyro.getAccelerationX());
}

// Y-axis acceleration, unit is G.
double MPU9250Block::getAccY()
{
    return convertAcc(accelgyro.getAccelerationY());
}

// Z-axis acceleration, unit is G.
double MPU9250Block::getAccZ()
{
    return convertAcc(accelgyro.getAccelerationZ());
}

double MPU9250Block::getGyroX()
{
    return convertGyro(accelgyro.getRotationX());
}

double MPU9250Block::getGyroY()
{
    return convertGyro(accelgyro.getRotationY());
}

double MPU9250Block::getGyroZ()
{
    return convertGyro(accelgyro.getRotationZ());
}

double MPU9250Block::getMagX()
{
    readMagData();
    return convertMag(mx);
}

double MPU9250Block::getMagY()
{
    readMagData();
    return convertMag(my);
}

double MPU9250Block::getMagZ()
{
    readMagData();
    return convertMag(mz);
}

double MPU9250Block::getDegreeToMagNorth()
{
    float pitch = asin(-getAccX());
    float roll = asin(getAccY()/cos(pitch));
    readMagData();
    float Mxyz[3] = {0.f};
    Mxyz[0] = (double) mx * 4800 / 8192;
	Mxyz[1] = (double) my * 4800 / 8192;
	Mxyz[2] = (double) mz * 4800 / 8192;

    float xh = Mxyz[0] * cos(pitch) + Mxyz[2] * sin(pitch);
    float yh = Mxyz[0] * sin(roll) * sin(pitch) + Mxyz[1] * cos(roll) - Mxyz[2] * sin(roll) * cos(pitch);
    float zh = -Mxyz[0] * cos(roll) * sin(pitch) + Mxyz[1] * sin(roll) + Mxyz[2] * cos(roll) * cos(pitch);
    float tiltheading = 180 * atan2(yh, xh)/PI;
    if(yh<0)    tiltheading +=360;

    return tiltheading;
}

double MPU9250Block::getPitch()
{
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
    accelgyro.getAcceleration(&x, &y, &z);
    const int pitch = (atan2(x, sqrt(y * y + z * z)) * 180.0) / PI;
    return pitch;
}

double MPU9250Block::getRoll()
{
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
    accelgyro.getAcceleration(&x, &y, &z);

    const int roll = (atan2(y, z) * 180.0) / PI;
    return roll;
}

double MPU9250Block::getYaw()
{
    return getDegreeToMagNorth();
}