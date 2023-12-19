//Счётчик для пинг- понга
//добавить аимации запуска/выигрыша
//add running text
#include <Arduino.h>
#include <EncButton.h>
#include <microLED.h>
#include "bitmap.h"
#include "FastLED.h"

//#define DEBUG 

#define EB_HOLD_TIME 400    // таймаут удержания (кнопка)
#define M_PIN 2       // пин матрицы
#define M_WIDTH 16    // ширина матрицы
#define M_HEIGHT 8    // высота матрицы
#define NUM_LEDS (M_WIDTH * M_HEIGHT) // для удобства запомним и количство ледов
#define COLOR_DEBTH 3

#define DIGIT_HEIGHT 5 //высота цифры

microLED<NUM_LEDS, M_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB, CLI_AVER> matrix(M_WIDTH, M_HEIGHT, ZIGZAG, LEFT_TOP, DIR_DOWN);
// тип матрицы: ZIGZAG - зигзаг, PARALLEL - параллельная
// угол подключения: LEFT_BOTTOM - левый нижний, LEFT_TOP - левый верхний, RIGHT_TOP - правый верхний, RIGHT_BOTTOM - правый нижний
// направление ленты из угла подключения: DIR_RIGHT - вправо, DIR_UP - вверх, DIR_LEFT - влево, DIR_DOWN - вниз
// шпаргалка по настройке матрицы в папке docs в библиотеке

Button enc(4);
Button btn1(6);
Button btn2(5);

uint8_t score0 = 0;
uint8_t score1 = 0;
uint8_t goal = 21; //до скольких очков игра

void start_anim()
{

}
void setup() {
  // Serial.begin(9600);
  matrix.setBrightness(60);
  matrix.clear();
  
  //Wire.setClock(800000L);   // макс. 800'000
  matrix.show();
  start_anim();
}

void print_digit(uint8_t digit, uint8_t num) // digit 0-3,  num 0-9
{
  uint8_t d = digit * 4;
  matrix.set(7, 2, mRed);// : двоеточие между очками
  matrix.set(7, 4, mRed);
  // digit>1 ?
  // цвет от позиции digit

  if (num>9)
  {
    uint8_t digit0 = num / 10;
    uint8_t digit1 = num % 10;
    print_digit(digit, digit0);
    print_digit(digit+1,digit1);
    return;
  }

  switch (num)
  {
  case 0:                                  // рисуем 0
    for (int i = 0; i < DIGIT_HEIGHT; i++) // заливка с нижнего левого угла до верхнего левого
    {
      matrix.set(d, i, mGreen);
    }
    for (int i = 0; i < DIGIT_HEIGHT; i++) // заливка с нижнего до верхнего
    {
      matrix.set(d + 2, i, mGreen);
    }
    matrix.set(d + 1, 0, mGreen);
    matrix.set(d + 1, DIGIT_HEIGHT - 1, mGreen);
    break;

  case 1: // рисуем 1
    matrix.set(d, 2, mGreen);
    matrix.set(d + 1, 3, mGreen);
    for (int i = 0; i < DIGIT_HEIGHT; i++) //
    {
      matrix.set(d + 2, i, mGreen);
    }
    break;

  case 2: // рисуем 2
    matrix.set(d, 0, mGreen);
    matrix.set(d + 1, 0, mGreen);
    matrix.set(d + 2, 0, mGreen);

    matrix.set(d, 1, mGreen);
    matrix.set(d + 1, 2, mGreen);
    matrix.set(d + 2, 2, mGreen);

    matrix.set(d + 2, 2, mGreen);
    matrix.set(d + 2, 3, mGreen);
    matrix.set(d + 2, 4, mGreen);
    break;

  case 3:
    for (int i = 0; i < DIGIT_HEIGHT; i++) //
    {
      matrix.set(d + 2, i, mGreen);
    }
    matrix.set(d + 1, 0, mGreen);
    matrix.set(d + 2, 0, mGreen);

    matrix.set(d + 1, 2, mGreen);
    matrix.set(d + 2, 2, mGreen);

    matrix.set(d + 1, 4, mGreen);
    matrix.set(d + 2, 4, mGreen);
    break;

  case 4:
    for (int i = 0; i < DIGIT_HEIGHT; i++) //
    {
      matrix.set(d + 2, i, mGreen);
    }
    matrix.set(d, 2, mGreen);
    matrix.set(d, 3, mGreen);
    matrix.set(d, 4, mGreen);
    
    matrix.set(d+1, 2, mGreen);
  break;

  default:
    break;
  }
}

boolean Put_in()
{
  if (enc.click())  //pts=0;
  {
    score0 = 0;
    score1 = 0;
    matrix.clear();
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
  print_digit(0, score0); 
  print_digit(2, score1);
  matrix.show();
  
  #ifdef DEBUG
    Serial.print(score0);
    Serial.print("\t");
    Serial.println(score1);
  #endif
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

        delay(80);
      }
      break;
    case 1:
      for (int i = 128; i > -250; i = i - 10)
      {
 
        delay(80);
      }
      break;
  }

  delay(2500);

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
