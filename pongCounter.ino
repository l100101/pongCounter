//Счётчик для пинг- понга
//добавить аимации запуска/выигрыша

#include <EncButton.h>
//#include <GyverTM1637.h>
#include <GyverOLED.h>
#include <microLED.h>
#include "bitmap.h"

#define EB_HOLD_TIME 400    // таймаут удержания (кнопка)
#define M_PIN 2       // пин матрицы
#define M_WIDTH 15    // ширина матрицы
#define M_HEIGHT 10    // высота матрицы
#define NUM_LEDS (M_WIDTH * M_HEIGHT) // для удобства запомним и количство ледов
#define COLOR_DEBTH 3

microLED<NUM_LEDS, M_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB, CLI_AVER> matrix(M_WIDTH, M_HEIGHT, ZIGZAG, LEFT_TOP, DIR_DOWN);
// тип матрицы: ZIGZAG - зигзаг, PARALLEL - параллельная
// угол подключения: LEFT_BOTTOM - левый нижний, LEFT_TOP - левый верхний, RIGHT_TOP - правый верхний, RIGHT_BOTTOM - правый нижний
// направление ленты из угла подключения: DIR_RIGHT - вправо, DIR_UP - вверх, DIR_LEFT - влево, DIR_DOWN - вниз
// шпаргалка по настройке матрицы в папке docs в библиотеке


Button enc(4);
Button btn1(6);
Button btn2(5);

byte score0 = 0;
byte score1 = 0;
byte goal = 21; //до скольких очков игра

void start_anim()
{
  for (int i = 5; i <= 120; i = i + 15)
  {
    oled.setCursorXY(0, 30);
    oled.print("PoNg CoUnTeR");
    oled.circle(i, 50, 5, OLED_FILL);        // окружность с центром в (x,y, с радиусом)
    delay(100);
    oled.update();
  }
  delay(2500);
  oled.clear();
}
void setup() {
  // Serial.begin(9600);
  matrix.setBrightness(60);
  matrix.clear();
  
  Wire.setClock(800000L);   // макс. 800'000
  matrix.show();
  start_anim();
}

void print_digit_0()
{
 // matrix.
}



boolean Put_in()
{
  if (enc.click())  //pts=0;
  {
    score0 = 0;
    score1 = 0;
    oled.clear();
    return 1;
  }
  if (btn1.hold()){  //pts--
    score0--; return 1;}

  if (btn2.hold()){  //pts--
    score1--; return 1;}

  if (btn1.click()){
    score0++; return 1;}

  if (btn2.click()){
    score1++;return 1;}

}
void showDisp()
{
  oled.setScale(2);
  oled.setCursorXY(0, 0);
  oled.print("goal:");
  oled.print(goal);
  oled.setScale(5);
  oled.setCursorXY(0, 32);
  oled.print(score0);
  oled.setCursorXY(50, 32);
  oled.print(":");
  oled.setCursorXY(70, 32);
  oled.print(score1);
  oled.update();
 
  matrix.show();
  //  Serial.print(score0);
  //  Serial.print("\t");
  //  Serial.println(score1);
}
void win0()
{

}
void win1()
{

}
void win(boolean player)// визуальные эффекты для выигрыша 1-го и 2-го игрока
{
  switch (player)
  {
    case 0:
      //win0();
      for (int i = 128; i > -250; i = i - 10)
      {
        oled.clear();
        oled.setCursorXY(i, 30);
        oled.print("Player 0 wins!");
        oled.update();
        delay(80);
      }
      break;
    case 1:
      for (int i = 128; i > -250; i = i - 10)
      {
        oled.clear();
        oled.setCursorXY(i, 30);
        oled.print("Player 1 wins!");
        oled.update();
        delay(80);
      }
      break;
  }

  oled.clear();
  oled.drawBitmap(0, 0, bitmap_128x64, 128, 64, BITMAP_NORMAL, BUF_ADD);
  oled.update();
  delay(2500);
  oled.clear();
  score0 = 0;
  score1 = 0;
}
void winCheck()
{
  if (score0 == goal || score1 == goal)
  {
    win(score1 > score0);
  }
}
void loop() {

  btn1.tick();//обязательный постоянный опрос
  btn2.tick();
  enc.tick();

  if (Put_in()) 
   matrix.clear();
 //чистим дисплей после любого действия
  winCheck();
  showDisp();//вывод на дисплей
}
