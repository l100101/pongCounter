//Счётчик для пинг- понга
#include <EncButton.h>
#include <GyverTM1637.h>

#define EB_HOLD_TIME 400    // таймаут удержания (кнопка)
#define CLK 2
#define DIO 3


GyverTM1637 disp(CLK, DIO);
EncButton enc(2, 3, 4);
Button btn1(5);
Button btn2(6);

byte score0 = 0;
byte score1 = 0;
byte goal = 11; //до скольких очков игра

void setup() {
  Serial.begin(9600);
  disp.clear();
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
}

void loop() {
  btn1.tick();//обязательный постоянный опрос
  btn2.tick();
  enc.tick();

  if (Put_in())//чистим дисплей после любого действия
    disp.clear();

  if (score0 == goal || score1 == goal)//если кто-то добрался до нужного очка :D
  {
    win(score1 > score0);           //запускаем победную анимацию 
  }

  showdisp();//вывод на дисплей
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

void showdisp()
{
  //disp.display(0, score0);    // 0 ячейка
  // disp.display(1, '.');    // 1 ячейка
 // disp.display(2, score1);    // 2 ячейка
  // disp.display(3, '.');    // 3 ячейка
 
  // скручивание прицельно (ячейка, ЦИФРА, скорость)
  disp.twist(0, score0, 70);
  disp.twist(2, score1, 70);
  
}

boolean Put_in()
{
  boolean q = 0;
  if (enc.left()) Serial.println("left");
  if (enc.right()) Serial.println("right");
  if (enc.leftH()) Serial.println("leftH");
  if (enc.rightH()) Serial.println("rightH");

  if (enc.click())  //pts=0;
  {
    //return 1;
    q = 1;
    score0 = 0;
    score1 = 0;
  }
  if (btn1.press())  //pts--
  {
    q = 1;
    score0--;
  }
  if (btn2.press())  //pts--
  {
    q = 1;
    score1--;
  }
  if (btn1.click())
  {
    q = 1;
    score0++;
  }
  if (btn2.click())
  {
    q = 1;
    score1++;
  }

  return q;
}
