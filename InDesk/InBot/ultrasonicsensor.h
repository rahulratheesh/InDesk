#include "sensor.h"

class UltrasonicSensor : public Sensor {
  
  public:
    UltrasonicSensor(int triggerPin, int echoPin, int maxDistance)
    : Sensor(maxDistance), sensor(triggerPin, echoPin, maxDistance) {}

    virtual unsigned int getDistance() {
      int distance = sensor.ping_cm();
      if (distance <= 0)
          return maxDistance;
       return distance;
    }
     
    private:
      NewPing sensor;
};

