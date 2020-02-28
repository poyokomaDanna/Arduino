#ifndef MOTOR_h
#define MOTOR_h

#include <Arduino.h>

#define ON HIGH
#define OFF LOW

#define PIN_MOTOR1_PWM	14
#define PIN_MOTOR2_PWM	15
#define PIN_MOTOR3_PWM	16
#define PIN_MOTOR4_PWM	13

#define PIN_MOTOR1_IN1	8
#define PIN_MOTOR1_IN2	9
#define PIN_MOTOR2_IN1	10
#define PIN_MOTOR2_IN2	11
#define PIN_MOTOR3_IN1	18
#define PIN_MOTOR3_IN2	19
#define PIN_MOTOR4_IN1	20
#define PIN_MOTOR4_IN2	21

typedef struct  {
	uint8_t speed;
	uint8_t in1;
	uint8_t in2;
} MotorParam_t;

class Motor
{
  public:
    Motor();
    void start(int16_t mtr1, int16_t mtr2, int16_t mtr3, int16_t mtr4);
    void stop();
    void brake();

    void mtr1_start(int16_t mtr);
    void mtr1_stop();
    void mtr1_brake();
    void mtr2_start(int16_t mtr);
    void mtr2_stop();
    void mtr2_brake();
    void mtr3_start(int16_t mtr);
    void mtr3_stop();
    void mtr3_brake();
    void mtr4_start(int16_t mtr);
    void mtr4_stop();
    void mtr4_brake();

  private:
    MotorParam_t checkMotorSpeed(int16_t mtr);
};


#endif
