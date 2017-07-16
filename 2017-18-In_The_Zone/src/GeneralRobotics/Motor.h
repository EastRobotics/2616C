#include <main.h>
class Motor {
    unsigned char chnl;
    int spd;
    public:
      void setValue(int);
      int getValue();
      Motor(int channel, int speed) {
        chnl = channel;
        spd = speed;
      }
};
