#include <Wire.h>
#include <adxl345_blockly.h>

void ADXL345Block::begin()
{
    _gestureFlags = 0;
    _adxl.powerOn();
    _adxl.setRangeSetting(8);
    _adxl.setActivityXYZ(1, 1, 1);

    // Sensitiity : low/150, mid/75, high/25
    // 0~255, 62.5mg per increment
    _adxl.setActivityThreshold(25);
    // So threshold = 25 * 62.5mg

    // Detect taps in the directions turned ON "_adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)
    _adxl.setTapDetectionOnXYZ(0, 0, 1);
    _adxl.setTapThreshold(50);
    _adxl.setTapDuration(15);
    _adxl.setDoubleTapLatency(80);
    _adxl.setDoubleTapWindow(200);
    _adxl.ActivityINT(1);
    _adxl.doubleTapINT(1);
    _adxl.singleTapINT(1);
}

float ADXL345Block::convertAcc(int acc)
{
    return acc * 15.6 / 1000.0f;
}

std::tuple<int, int, int> ADXL345Block::getAccXYZ()
{
    int accXYZ[3] = {0};
    _adxl.readAccel(accXYZ);
    return std::make_tuple(accXYZ[0], accXYZ[1], accXYZ[2]);
}

float ADXL345Block::getX()
{
    return convertAcc(std::get<0>(getAccXYZ()));
}

float ADXL345Block::getY()
{
    return convertAcc(std::get<1>(getAccXYZ()));
}

float ADXL345Block::getZ()
{
    return convertAcc(std::get<2>(getAccXYZ()));
}

float ADXL345Block::getPitch()
{
    int accXYZ[3] = {0};
    _adxl.readAccel(accXYZ);
    const int adxl_pitch = (atan2(accXYZ[0], sqrt(accXYZ[1] * accXYZ[1] + accXYZ[2] * accXYZ[2])) * 180.0) / PI;
    return adxl_pitch;
}

float ADXL345Block::getRoll()
{
    int accXYZ[3] = {0};
    _adxl.readAccel(accXYZ);
    const int adxl_roll = (atan2(accXYZ[1], (sqrt(accXYZ[0] * accXYZ[0] + accXYZ[1] * accXYZ[1]))) * 180.0) / PI;
    return adxl_roll;
}

void ADXL345Block::detectGesture()
{
    _gestureFlags = _adxl.getInterruptSource();
}

bool ADXL345Block::isTapDetected()
{
    return _adxl.triggered(_gestureFlags, ADXL345_SINGLE_TAP);
}

bool ADXL345Block::isDoubleTapDetected()
{
    return _adxl.triggered(_gestureFlags, ADXL345_DOUBLE_TAP);
}

bool ADXL345Block::isActivityDetected()
{
    return _adxl.triggered(_gestureFlags, ADXL345_ACTIVITY);
}
