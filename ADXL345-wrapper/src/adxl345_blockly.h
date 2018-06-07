#include <SparkFun_ADXL345.h>
#include <tuple>

class ADXL345Block {
public:
    // must call this in setup()
    void begin();

    // X-axis acceleration, unit is G.
    float getX();

    // Y-axis acceleration, unit is G.
    float getY();

    // Z-axis acceleration, unit is G.
    float getZ();

    // Convert acceleration to a "Pitch" of the sensor
    float getPitch();

    // Convert acceleration to a "Roll" of the sensor
    float getRoll();

    // detect for tap, double tap, and activity
    void detectGesture();

    // get detection result of tap
    bool isTapDetected();

    // get detection result of double tap
    bool isDoubleTapDetected();

    // get detection result of activity
    bool isActivityDetected();
    
protected:
    ADXL345 _adxl;
    byte _gestureFlags;
    float convertAcc(int acc);
    std::tuple<int, int, int> getAccXYZ();
};