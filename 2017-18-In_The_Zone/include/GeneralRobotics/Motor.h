#include "../main.h"
class Motor {
  int pwm_value;
  unsigned char port_number;
  enum relationToWheel { direct, chain, gearedPos, gearedNeg};
  public:
    int getPWMValue();
    void setPWMValue();
    int getPortNumber();
};
