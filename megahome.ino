#include <Button.h>


#define hallSW0 1 // выключатель в холе кнопка 0

#define hallSW1 2 // выключатель в холе кнопка 1
#define hallLight 3 // коридор свет
bool bhallLight = false;

#define bathroomSW0 4 // ванная выключатель
#define bathroomLight 5 // ванная свет
bool bbathroomLight = false;
#define bathroomFan 6 // ванная вентилятор
bool bbathroomFan = false;
int ibathroomFan = 0;
#define bathroomBrace 7 // ванная бра
bool bbathroomBrace = false;

#define wcSW0 8 // туалет выключатель
#define wcLight 9 // теалет свет
bool bwcLight = false;
#define wcFan 10 // туалет выключатель
bool bwcFan = false;
int iwcFan = 0;
#define wcBrace 11 // туалет бра
bool bwcBrace = false;


#define kitchenSW0_0 12 // кухня выключатель кнопка 0
#define kitchenSW0_1 13 // кухня выключатель кнопка 1
#define kitchenSW1_0 14 // кухня выключатель кнопка возле поверхности кнопка 0
#define kitchenLight 15
bool bkitchenLight = false;
#define kitchenLight1 16
bool bkitchenLight1 = false;
#define kitchenLight2 17
bool bkitchenLight2 = false;
#define kitchenLightDots 18
bool bkitchenLightDots = false;

#define balconySW0 19
#define balconyLight 20
bool bbalconyLight = false;

#define livingRoomSW0 21
#define livingRoomSW1 22
#define livingRoomLight 23
bool blivingRoomLight = false;
#define livingRoomBrace 24
bool blivingRoomBrace = false;

#define bedRoomSW0_0 25
#define bedRoomSW0_1 26
#define bedRoomSW1_0 27
#define bedRoomSW1_1 28
#define bedRoomSW2_0 29
#define bedRoomSW2_1 30
#define bedRoomLight 31
bool bbedRoomLight = false;
#define bedRoomBrace0 32
bool bbedRoomBrace0 = false;
#define bedRoomBrace1 33
bool bbedRoomBrace1 = false;

#define childRoomSW0_0 34
#define childRoomSW0_1 35
#define childRoomSW1_0 36
#define childRoomSW1_1 37
#define childRoomLight 38
bool bchildRoomLight = false;
#define childRoomBrace 39
bool bchildRoomBrace = false;


Button hButton;


void setup() {
  hButton.NO(); // N.O. Normal Open
  // hButton.NC(); // N.C. Normal Closed
  //hButton.pullUp();
  hButton.pullDn();
  hButton.duration_bounce       (  50);
  hButton.duration_click_Db     ( 250);
  hButton.duration_inactivity_Up(5000);
  hButton.duration_inactivity_Dn(1000);
  hButton.duration_press        ( 500);
  hButton.button( hallSW0, hallSW1, bathroomSW0, wcSW0, kitchenSW0_0, kitchenSW0_1, kitchenSW1_0, balconySW0, livingRoomSW0, livingRoomSW1,bedRoomSW0_0, bedRoomSW0_1, bedRoomSW1_0, bedRoomSW1_1, bedRoomSW2_0, bedRoomSW2_1,childRoomSW0_0, childRoomSW0_1, childRoomSW1_0, childRoomSW1_1); // arduino pins connected to button



  // put your setup code here, to run once:


  Serial.begin(9600);

}

void loop() {
  hButton.read();

}
