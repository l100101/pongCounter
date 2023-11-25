//Счётчик для пинг- понга
#include <EncButton.h>
//#include <GyverTM1637.h>
#include <GyverOLED.h>

#define EB_HOLD_TIME 400    // таймаут удержания (кнопка)
//#define CLK 2
//#define DIO 3


//GyverTM1637 disp(CLK, DIO);
GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
EncButton enc(2, 3, 4);
Button btn1(5);
Button btn2(6);

byte score0 = 0;
byte score1 = 0;
byte goal = 11; //до скольких очков игра

void setup() {
  Serial.begin(9600);
  // disp.clear();
  //  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
   oled.init();
   Wire.setClock(800000L);   // макс. 800'000
}

void Put_in()
{
  //  if (enc.left()) Serial.println("left");
  //  if (enc.right()) Serial.println("right");
  //  if (enc.leftH()) Serial.println("leftH");
  //  if (enc.rightH()) Serial.println("rightH");
  if (enc.click())  //pts=0;
  {
    score0 = 0;
    score1 = 0;
  }
  if (btn1.hold())  //pts--
    score0--;

  if (btn2.hold())  //pts--
    score1--;

  if (btn1.click())
    score0++;

  if (btn2.click())
    score1++;

}
void showDisp()
{
  //  disp.display(0, score0);    // 0 ячейка
  //  disp.display(1, '.');    // 1 ячейка
  //  disp.display(2, score1);    // 2 ячейка
  //  disp.display(3, '.');    // 3 ячейка

    oled.setScale(2);
    oled.setCursorXY(0, 0);
    oled.print(score0);
    oled.setCursorXY(64, 0);
    oled.print(score1);
    oled.update();

  Serial.print(score0);
  Serial.print("\t");
  Serial.println(score1);
}

void win(boolean player)// визуальные эффекты для выигрыша 1-го и 2-го игрока
{
  switch (player)
  {
    case 0:
      break;
    case 1:
      break;
  }
}

void loop() {
  btn1.tick();//обязательный постоянный опрос
  btn2.tick();

  Put_in();//чистим дисплей после любого действия
  showDisp();//вывод на дисплей
  winCheck();
  if (score0 == goal || score1 == goal)
  {
    win(score1 > score0);
  }
  //
  //showdisp();//вывод на дисплей
}
