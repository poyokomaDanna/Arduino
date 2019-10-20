#include <Wire.h>

//モーターの制御ピンの設定
#define MTR_1_A 2
#define MTR_1_B 4
#define MTR_2_A 5
#define MTR_2_B 7
#define MTR_3_A 8
#define MTR_3_B 10
#define MTR_4_A 12
#define MTR_4_B 13

//モーターのPWMピンの設定
#define MTR_1_PWM 3
#define MTR_2_PWM 6
#define MTR_3_PWM 9
#define MTR_4_PWM 11

//制御内容保持用構造体
typedef struct _params {
  union {
    uint8_t dir;
    struct {
      unsigned char in1: 1;
      unsigned char in2: 1;
      unsigned char dummy: 6;
    };
  };
  uint8_t speed;
} params;

//出力ピンを初期設定するための設定
const uint8_t MOTOR_IO[8] = {MTR_1_A, MTR_1_B, MTR_2_A, MTR_2_B, MTR_3_A, MTR_3_B, MTR_4_A, MTR_4_B};
//モーター毎のピン割当設定
const uint8_t MOTOR_PINS[4][3] = {
  {MTR_1_A, MTR_1_B, MTR_1_PWM},
  {MTR_2_A, MTR_2_B, MTR_2_PWM},
  {MTR_3_A, MTR_3_B, MTR_3_PWM},
  {MTR_4_A, MTR_4_B, MTR_4_PWM},
};

//初期化処理
void setup() {
  uint8_t i;
  // put your setup code here, to run once:
  Wire.begin(0x0a) ; //アドレスを設定
  Wire.onReceive(I2ConReceive); //割り込み関数の指定

  //出力ピンの設定
  for (i = 0; i < 8; i++) {
    pinMode(MOTOR_IO[i], OUTPUT);
  }
}

void loop() {
  //I2Cで受信したら処理を行うのでここでの処理なし
}

//I2C受信割り込み
void I2ConReceive(int count) {
  uint8_t idx = 0;
  uint8_t buf[8] = {};
  uint8_t i;
  params param = {};

  //受信したデータを取得
  while (Wire.available() > 0) {
    buf[idx++] = (uint8_t)Wire.read();
    if (idx >= 8) break;
  }

  //受信数が少ない時は処理終了
  if (idx < 4) return;

  //先頭4個のモーターを制御
  for (i = 0; i < 4; i++) {
    param = getParams(buf[i]);
    changeSpeedParam(i, param);
  }
}

//引数から方向とスピードを分離
params getParams(uint8_t speed)
{
  params param = {};
  uint8_t miSpeed = speed & 0x7f;

  if (speed == 0x80) {
    param.dir = 3;
    param.speed = 0;
  } else if (speed == 0) {
    param.dir = 0;
    param.speed = 0;
  } else if (speed != miSpeed) {
    if (miSpeed > 100) {
      miSpeed = 100;
    }
    param.dir = 2;
    param.speed = miSpeed;
  } else {
    if (speed > 100) {
      speed = 100;
    }
    param.dir = 1;
    param.speed = speed;
  }
  return param;
}

//指定のモーターの動きを変更
void changeSpeedParam(uint8_t port, params param) {
  analogWrite(MOTOR_PINS[port][2], param.speed);
  digitalWrite(MOTOR_PINS[port][0], param.in1);
  digitalWrite(MOTOR_PINS[port][1], param.in2);
}
