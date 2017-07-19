#include <main.h>
class Wheel {
    unsigned char chnl;

    int v_t_x;
    int v_t_y;
    int v_w;
    public:
      void setValue(int);
      int getValue();
      int getVector(char);
      void setVector(char, int);
      Wheel() {
        chnl = 0;
        v_t_x = 0;
        v_t_y = 0;
        v_w = 0;
      };
      Wheel(unsigned char channel) {
        chnl = channel;
        v_t_x = 0;
        v_t_y = 0;
        v_w = 0;
      };
};
int Wheel::getVector(char movement_vector) {
  switch (movement_vector) {
    case 'x':
      return v_t_x;
      break;
    case 'y':
      return v_t_y;
      break;
    case 'r' or 'w':
    return v_w;
      break;
  }
}
void Wheel::setVector(char movement_vector, int value) {
  switch (movement_vector) {
    case 'x':
      v_t_x = value;
      break;
    case 'y':
      v_t_y = value;
      break;
    case 'r' or 'w':
    v_w = value;
      break;
  }
}
void Wheel::setValue(int speed) {
    motorSet(chnl, speed);
  }
