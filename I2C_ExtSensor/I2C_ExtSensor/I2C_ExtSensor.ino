#include <Wire.h>

//拡張センサーボードID(1-8)
#define SENSOR_ID 1
//センサーIDに対応するI2Cアドレス
#define I2C_ID 0x17 + SENSOR_ID

//UNOなので4個、ボードに合わせて変更する
//UNOはI2CがADC4,5を使っているのでポートが2個減る
#define ADC_COUNT 4
//ADC読込バッファ
uint16_t AdcBuf[10] = {};
//I2C返却データバッファ
uint8_t writeBuf[24] = {};
//I2C返却データ数
uint8_t writeLen = 0;

void setup() {
  Wire.begin(I2C_ID) ; //アドレスを設定
  Wire.onReceive(I2ConReceive); //割り込み関数の指定(I2C 受信)
  Wire.onRequest(I2ConRequest); //割り込み関数の指定(I2C 送信)
}

void loop() {
  uint8_t i;

  //ループで送信値を取得する
  for (i = 0; i < ADC_COUNT; i++) {
    AdcBuf[i] = analogRead(i);
  }
}

//I2C受信割り込み
void I2ConReceive(int count) {
  uint8_t idx = 0;
  uint8_t buf[16] = {};
  uint8_t i;

  //受信したデータを取得
  while (Wire.available() > 0) {
    buf[idx++] = (uint8_t)Wire.read();
    if (idx >= 16) break;
  }

  //受信数が少ない時は処理終了
  if (idx < 2) return;

  //コマンド解析
  switch (buf[1]) {
    //IO設定リード
    //センサーモニタの最初にポートの設定情報を取得する
    //すべて入力ポートを返却する
    case 0x80:
      for (i = 0; i < 10; i++) {
        writeBuf[i] = 1;
      }
      writeLen = 10;
      break;

    //センサー値リード
    //センサー値取得コマンド。センサーモニタ用の10ポートまとめての時と個別にポートの値を取得する時で分かれる
    case 0x81:
      //受信数が少ない時は処理終了
      if (idx < 3) return;

      writeLen = 0;
      if (buf[2] >= 10) {
        //ポート番号が10以上の時は10ポートまとめて
        for (i = 0; i < 10; i++) {
          writeBuf[writeLen++] = (AdcBuf[i] & 0xff);
          writeBuf[writeLen++] = (AdcBuf[i] >> 8);
        }
      } else {
        //ポート番号が0-9の時は指定のポート1ポートのみ
        writeBuf[writeLen++] = (AdcBuf[buf[2]] & 0xff);
        writeBuf[writeLen++] = (AdcBuf[buf[2]] >> 8) & 0xff;
      }
      break;
  }
}

//I2C送信リクエスト割り込み
void I2ConRequest() {
  //受信割り込みで設定したデータを送信する
  Wire.write(writeBuf, writeLen);
}
