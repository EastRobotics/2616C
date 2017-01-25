typedef struct {
  int portNum;
  unsigned char mtrType;
  int speed;
} tMotor;

typedef struct {
  tMotor mtr1;
  tMotor mtr2;
} tMotorSet;
