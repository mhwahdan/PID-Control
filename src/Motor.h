

class Motor
{
private:
  long prevT = 0;
  float angle;
  float RPM;
public:
  /* data */
  int pwm;
  int in1; 
  int in2;
  int ppr;
  Motor(int in1, int in2, int ppr);
  ~Motor();
  int setMotor(int power, char direction);
  int stopMotor();
  float updateRPM(int increment);
  float updateAngle(int increment);
  float getRPM();
  float getAngle();
};

