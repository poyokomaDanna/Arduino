#include "Motor.h"

Motor::Motor() {
	pinMode(PIN_MOTOR1_IN1, OUTPUT);
	pinMode(PIN_MOTOR1_IN2, OUTPUT);
	pinMode(PIN_MOTOR2_IN1, OUTPUT);
	pinMode(PIN_MOTOR2_IN2, OUTPUT);
	pinMode(PIN_MOTOR3_IN1, OUTPUT);
	pinMode(PIN_MOTOR3_IN2, OUTPUT);
	pinMode(PIN_MOTOR4_IN1, OUTPUT);
	pinMode(PIN_MOTOR4_IN2, OUTPUT);
	start(0,0,0,0);
}

void Motor::start(int16_t mtr1, int16_t mtr2, int16_t mtr3, int16_t mtr4) {
	mtr1_start(mtr1);
	mtr2_start(mtr2);
	mtr3_start(mtr3);
	mtr4_start(mtr4);
}
void Motor::stop() {
	mtr1_stop();
	mtr2_stop();
	mtr3_stop();
	mtr4_stop();
}
void Motor::brake() {
	mtr1_brake();
	mtr2_brake();
	mtr3_brake();
	mtr4_brake();
}

void Motor::mtr1_start(int16_t mtr) {
	MotorParam_t param = checkMotorSpeed(mtr);
	digitalWrite(PIN_MOTOR1_IN1, param.in1);
	digitalWrite(PIN_MOTOR1_IN2, param.in2);
	analogWrite(PIN_MOTOR1_PWM, param.speed);
}
void Motor::mtr1_stop() {
	digitalWrite(PIN_MOTOR1_IN1, OFF);
	digitalWrite(PIN_MOTOR1_IN2, OFF);
}
void Motor::mtr1_brake() {
	digitalWrite(PIN_MOTOR1_IN1, ON);
	digitalWrite(PIN_MOTOR1_IN2, ON);
}

void Motor::mtr2_start(int16_t mtr) {
	MotorParam_t param = checkMotorSpeed(mtr);
	digitalWrite(PIN_MOTOR2_IN1, param.in1);
	digitalWrite(PIN_MOTOR2_IN2, param.in2);
	analogWrite(PIN_MOTOR2_PWM, param.speed);
}
void Motor::mtr2_stop() {
	digitalWrite(PIN_MOTOR2_IN1, OFF);
	digitalWrite(PIN_MOTOR2_IN2, OFF);
}
void Motor::mtr2_brake() {
	digitalWrite(PIN_MOTOR2_IN1, ON);
	digitalWrite(PIN_MOTOR2_IN2, ON);
}

void Motor::mtr3_start(int16_t mtr) {
	MotorParam_t param = checkMotorSpeed(mtr);
	digitalWrite(PIN_MOTOR3_IN1, param.in1);
	digitalWrite(PIN_MOTOR3_IN2, param.in2);
	analogWrite(PIN_MOTOR3_PWM, param.speed);
}
void Motor::mtr3_stop() {
	digitalWrite(PIN_MOTOR3_IN1, OFF);
	digitalWrite(PIN_MOTOR3_IN2, OFF);
}
void Motor::mtr3_brake() {
	digitalWrite(PIN_MOTOR3_IN1, ON);
	digitalWrite(PIN_MOTOR3_IN2, ON);
}

void Motor::mtr4_start(int16_t mtr) {
	MotorParam_t param = checkMotorSpeed(mtr);
	digitalWrite(PIN_MOTOR4_IN1, param.in1);
	digitalWrite(PIN_MOTOR4_IN2, param.in2);
	analogWrite(PIN_MOTOR4_PWM, param.speed);
}
void Motor::mtr4_stop() {
	digitalWrite(PIN_MOTOR4_IN1, OFF);
	digitalWrite(PIN_MOTOR4_IN2, OFF);
}
void Motor::mtr4_brake() {
	digitalWrite(PIN_MOTOR4_IN1, ON);
	digitalWrite(PIN_MOTOR4_IN2, ON);
}

MotorParam_t Motor::checkMotorSpeed(int16_t mtr) {
	MotorParam_t param = {};
	uint16_t speed = abs(mtr);
	if (mtr == 0) {
		param.speed = 0;
		param.in1 = OFF;
		param.in2 = OFF;
	} else if (speed > 255) {
		param.speed = 0;
		param.in1 = ON;
		param.in2 = ON;
	} else {
		param.speed = speed;
		param.in1 = (mtr > 0)?ON:OFF;
		param.in2 = (mtr < 0)?ON:OFF;
	}
	return param;
}
