#include <Wire.h>
#include "DS3231.h"

#include <Button.h>

class aButton {
  public:
    int pin;
    String bname;
    aButton(String inname, int inpin) {
      pin = inpin;
      bname = inname;
    }
    ~aButton() {}
};

RTClib RTC;
DS3231 Clock;

#define hallSW0 1 // выключатель в холе кнопка 0
aButton test("23", 1);
#define hallSW1 2 // выключатель в холе кнопка 1
#define hallLight 3 // коридор свет

#define bathroomSW0 4 // ванная выключатель
#define bathroomLight 5 // ванная свет
#define bathroomFan 6 // ванная вентилятор
#define bathroomBrace 7 // ванная бра

#define wcSW0 8 // туалет выключатель
#define wcLight 9 // теалет свет
#define wcFan 10 // туалет выключатель
#define wcBrace 11 // туалет бра

#define kitchenSW0_0 12 // кухня выключатель кнопка 0
#define kitchenSW0_1 13 // кухня выключатель кнопка 1
#define kitchenSW1_0 14 // кухня выключатель кнопка возле поверхности кнопка 0
#define kitchenLight 15
#define kitchenLight1 16
#define kitchenLight2 17
#define kitchenLightDots 18

#define balconySW0 19
#define balconyLight 20

#define livingRoomSW0 21
#define livingRoomSW1 22
#define livingRoomLight 23
#define livingRoomBrace 24

#define bedRoomSW0_0 25
#define bedRoomSW0_1 26
#define bedRoomSW1_0 27
#define bedRoomSW1_1 28
#define bedRoomSW2_0 29
#define bedRoomSW2_1 30
#define bedRoomLight 31
#define bedRoomBrace0 32
#define bedRoomBrace1 33

#define childRoomSW0_0 34
#define childRoomSW0_1 35
#define childRoomSW1_0 36
#define childRoomSW1_1 37
#define childRoomLight 38
#define childRoomBrace 39

Button hButton;


void setup() {
  hButton.NO(); // N.O. Normal Open
  // hButton.NC(); // N.C. Normal Closed
  hButton.pullUp();
  // hButton.pullDn();
  hButton.duration_bounce       (  50);
  hButton.duration_click_Db     ( 250);
  hButton.duration_inactivity_Up(5000);
  hButton.duration_inactivity_Dn(1000);
  hButton.duration_press        ( 500);
  hButton.button( hallSW0, 4, 9, 7, 8); // arduino pins connected to button



  // put your setup code here, to run once:


  Serial.begin(9600);
  Wire.begin();
  
//  Clock.setSecond(30);
//    Clock.setMinute(15);
//    Clock.setHour(8);
//    Clock.setDate(29);
//    Clock.setMonth(07);
//    Clock.setYear(18);
  //  Clock.setDoW(DoW);

}

void loop() {
  delay(1000);

  DateTime now = RTC.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

//  Serial.print(" since midnight 1/1/1970 = ");
//  Serial.print(now.unixtime());
//  Serial.print("s = ");
//  Serial.print(now.unixtime() / 86400L);
//  Serial.println("d");
}
