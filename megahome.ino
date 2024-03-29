#include "Button.h"
#include "Timer.h"

Timer myTimer;

#define mySECOND (1000L)
#define myMINUTE (60 * mySECOND)
#define myHOUR (60 * myMINUTE)
#define myDAY (24 * myHOUR)

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) ((_time_ % SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) (_time_ / SECS_PER_DAY)

#define hallSW0 14 // выключатель в холе кнопка 0

#define hallSW1 2   // выключатель в холе кнопка 1
#define hallLight 3 // коридор свет
bool bhallLight = false;
int8_t hallTimer = 0; // Таймер холла
int8_t allTimer = 0;  // общий таймер

#define bathroomSW0 4   // ванная выключатель
#define bathroomLight 5 // ванная свет
bool bbathroomLight = false;
#define bathroomFan 6 // ванная вентилятор
bool bbathroomFan = false;
int ibathroomFan = 0;
int8_t bathroomTimer = 0;

#define bathroomBrace 7 // ванная бра
bool bbathroomBrace = false;

#define wcSW0 8   // туалет выключатель
#define wcLight 44 // теалет свет
bool bwcLight = false;
#define wcFan 43 // туалет выключатель
bool bwcFan = false;
int iwcFan = 0;
int8_t wcTimer = 0;
#define wcBrace 45 // туалет бра
bool bwcBrace = false;

#define kitchenSW0_0 15 // кухня выключатель кнопка 0
#define kitchenSW0_1 16 // кухня выключатель кнопка 1
#define kitchenSW1_0 17 // кухня выключатель кнопка возле поверхности кнопка 0
#define kitchenLight 18
bool bkitchenLight = false;
#define kitchenLight1 19
bool bkitchenLight1 = false;
#define kitchenLight2 20
bool bkitchenLight2 = false;
#define kitchenLightDots 21
bool bkitchenLightDots = false;

#define balconySW0 22
#define balconyLight 23
bool bbalconyLight = false;

#define livingRoomSW0 24
#define livingRoomSW1 25
#define livingRoomLight 26
bool blivingRoomLight = false;
#define livingRoomBrace 27
bool blivingRoomBrace = false;

#define bedRoomSW0_0 29 //Mykola
#define bedRoomSW0_1 28 //Mykola  
#define bedRoomSW1_0 30
#define bedRoomSW1_1 31
#define bedRoomSW2_0 32
#define bedRoomSW2_1 33
#define bedRoomLight 34
bool bbedRoomLight = false;
#define bedRoomBrace0 35
bool bbedRoomBrace0 = false;
#define bedRoomBrace1 36
bool bbedRoomBrace1 = false;

#define childRoomSW0_0 37
//#define childRoomSW0_1 38
#define childRoomSW1_0 38
//#define childRoomSW1_1 40
#define childRoomLight 41
bool bchildRoomLight = false;
#define childRoomBrace 42
bool bchildRoomBrace = false;

#define inOutDoorSensor 12

Button hButton;

unsigned long HallTimeOff = 0;

#define ON HIGH
#define OFF LOW

#define ON2 HIGH
#define OFF2 LOW

void setup()
{
  Serial.begin(9600);
  //pinMode(inOutDoorSensor, INPUT);
  hButton.NO(); // N.O. Normal Open
  // hButton.NC(); // N.C. Normal Closed
  //hButton.pullUp();
  hButton.pullDn(); // - подтяжка пинов кнопок к GND
  hButton.duration_bounce(50);
  hButton.duration_click_Db(250);
  hButton.duration_inactivity_Up(5000);
  hButton.duration_inactivity_Dn(1000);
  hButton.duration_press(500);
  hButton.button(hallSW0 //0
                  , hallSW1 //1
                  , bathroomSW0 //2
                  , wcSW0 //3
                  , kitchenSW0_0 //4
                  , kitchenSW0_1 //5
                  , kitchenSW1_0 //6
                  , balconySW0 //7
                  , livingRoomSW0 //8
                  , livingRoomSW1 //9
                  , bedRoomSW0_0 //10
                  , bedRoomSW0_1  //11
                  , bedRoomSW1_0  //12
                  , bedRoomSW1_1  //13
                  , bedRoomSW2_0  //14
                  , bedRoomSW2_1  //15
                  , childRoomSW0_0  //16
                  //, childRoomSW0_1  //17
                  , childRoomSW1_0  //17
                  // , childRoomSW1_1  //19
                  , inOutDoorSensor //18
                  ); // arduino pins connected to button

  //pinMode(inOutDoorSensor, INPUT); // подключение
  digitalWrite(hallLight, LOW);
  pinMode(hallLight, OUTPUT);
  digitalWrite(hallLight, OFF);

  pinMode(bathroomLight, OUTPUT);
  pinMode(bathroomBrace, OUTPUT);
  pinMode(bathroomFan, OUTPUT);
  digitalWrite(bathroomLight, OFF);
  digitalWrite(bathroomBrace, OFF);
  digitalWrite(bathroomFan, OFF);

  pinMode(wcLight, OUTPUT);
  pinMode(wcBrace, OUTPUT);
  pinMode(wcFan, OUTPUT);
  digitalWrite(wcLight, OFF);
  digitalWrite(wcBrace, OFF);
  digitalWrite(wcFan, OFF);

  //digitalWrite(wcLight, LOW);
  pinMode(kitchenLight, OUTPUT);
  digitalWrite(kitchenLight, OFF);

  pinMode(kitchenLight1, OUTPUT);
  digitalWrite(kitchenLight1, OFF);

  pinMode(kitchenLight2, OUTPUT);
  digitalWrite(kitchenLight2, OFF);

  pinMode(kitchenLightDots, OUTPUT);
  digitalWrite(kitchenLightDots, OFF);

  //balconyLight
  pinMode(balconyLight, OUTPUT);
  digitalWrite(balconyLight, OFF);

  pinMode(livingRoomLight, OUTPUT);
  digitalWrite(livingRoomLight, OFF2);

  //livingRoomBrace

  pinMode(livingRoomBrace, OUTPUT);
  digitalWrite(livingRoomBrace, OFF2);

  pinMode(bedRoomLight, OUTPUT);
  digitalWrite(bedRoomLight, OFF2);

  pinMode(bedRoomBrace0, OUTPUT);
  digitalWrite(bedRoomBrace0, OFF2);

  pinMode(bedRoomBrace1, OUTPUT);
  digitalWrite(bedRoomBrace1, OFF2);

  pinMode(childRoomLight, OUTPUT);
  digitalWrite(childRoomLight, OFF2);

  pinMode(childRoomBrace, OUTPUT);
  digitalWrite(childRoomBrace, OFF2);
  // put your setup code here, to run once:
}

bool OpenInOutDoorSensor = false;
bool ballOFF = false;

void WCFanOFF()
{
  Serial.println("WCFan timer=OFF");
  digitalWrite(wcFan, OFF);
  myTimer.stop(wcTimer);
  wcTimer = 0;
}

void BathRoomFanOFF()
{
  Serial.println("bathroomFan timer=OFF");
  digitalWrite(bathroomFan, OFF);
  myTimer.stop(bathroomTimer);
  bathroomTimer = 0;
}

void HallLightOFF()
{
  Serial.println("hallLight timer end=OFF");
  digitalWrite(hallLight, OFF);
  myTimer.stop(hallTimer);
  hallTimer = 0;
}

void allOFF(bool withHall = false)
{
  Serial.print("allOFF");
  if (withHall)
  {
    Serial.println(" with hall");
    digitalWrite(hallLight, OFF);
  }
  digitalWrite(bathroomLight, OFF);
  digitalWrite(bathroomBrace, OFF);
  digitalWrite(bathroomFan, OFF);
  
  digitalWrite(wcLight, OFF);
  digitalWrite(wcBrace, OFF);
  digitalWrite(wcFan, OFF);

  digitalWrite(kitchenLight, OFF);
  digitalWrite(kitchenLight1, OFF);
  digitalWrite(kitchenLight2, OFF);
  digitalWrite(kitchenLightDots, OFF);

  digitalWrite(balconyLight, OFF);

  digitalWrite(livingRoomLight, OFF2);
  digitalWrite(livingRoomBrace, OFF2);

  digitalWrite(bedRoomLight, OFF2);
  digitalWrite(bedRoomBrace0, OFF2);
  digitalWrite(bedRoomBrace1, OFF2);

  digitalWrite(childRoomLight, OFF2);
  digitalWrite(childRoomBrace, OFF2);

  Serial.println("");
}

void allLightsOFF()
{
  Serial.println("allTimer timer=OFF");
  if (!OpenInOutDoorSensor)
  {
    allOFF(true);
    myTimer.stop(allTimer);
    allTimer = 0;
  }
  else
  {
    myTimer.stop(allTimer);
    allTimer = 0;
    allTimer = myTimer.after(1 * myMINUTE, &allLightsOFF);
  }
  ballOFF = false;
}

void loop()
{
  myTimer.update();
  // bool val = digitalRead(inOutDoorSensor);
  // if ((!OpenInOutDoorSensor) && (!val) && (digitalRead(hallLight) == OFF))
  // {
  //   digitalWrite(hallLight, ON);
  //   Serial.print("in out door sensor=");
  //   Serial.println("ON");
  //   OpenInOutDoorSensor = true;
  //   HallTimeOff = millis();
  // }
  // else
  // {
  //   OpenInOutDoorSensor = false;
  // }
  // if ((digitalRead(hallLight) == ON) && (HallTimeOff > 0) && (millis() - HallTimeOff >= 60000))
  // {
  //   Serial.println("all off timer");
  //   HallTimeOff = 0;
  //   allOFF(true);
  // }

  hButton.read();
//
#pragma region OutDoor //TODO доделать
  if (hButton.event_click_Dn(18) == 1) 
  {
    Serial.println("OutDoor event_click_Dn");
    OpenInOutDoorSensor = false;
    if ((bhallLight == OFF) && (!ballOFF))
    {
      ballOFF = false;
      Serial.println("start timer hall light off");
      hallTimer = myTimer.after(2 * myMINUTE, &HallLightOFF);
    }
    else
    {
      ballOFF = false;
      hallTimer = myTimer.after(2 * myMINUTE, &allLightsOFF);
    }
  }
  if (hButton.event_click_Up(18) == 1)
  {
    Serial.println("OutDoor event_click_Up");
    digitalWrite(hallLight, ON);
    OpenInOutDoorSensor = true;
    myTimer.stop(hallTimer);
    hallTimer = 0;
    //ballOFF = false;
  }
#pragma endregion

#pragma region hall
#pragma region hallSW0
  if (hButton.event_click_Dn(0) == 1)
  {
    Serial.println("hallSW0");
    bhallLight = !digitalRead(hallLight);
    digitalWrite(hallLight, bhallLight);
  }
  if (hButton.event_click_Db(0) == 1)
  {
  }
  if (hButton.event_press_short(0) == 1)
  {
  }
  if (hButton.event_press_long(0) == 1)
  {
  }
#pragma endregion

#pragma region hallSW1
  if (hButton.event_click_Dn(1) == 1)
  {
    ///HallTimeOff = millis();
    ballOFF = true;
    Serial.println("hallSW1");
    allOFF(false);
  }
  if (hButton.event_click_Db(1) == 1)
  {
    bhallLight = !digitalRead(hallLight);
    digitalWrite(hallLight, bhallLight);
  }
  if (hButton.event_press_short(1) == 1)
  {
  }
  if (hButton.event_press_long(1) == 1)
  {
  }
#pragma endregion
#pragma endregion

#pragma region bathroom
  if (hButton.event_click_Dn(2) == 1)
  {
    Serial.println("bathroomSW0");
    bbathroomLight = !digitalRead(bathroomLight);
    Serial.println(bbathroomLight);
    digitalWrite(bathroomLight, bbathroomLight);
    digitalWrite(bathroomBrace, bbathroomLight);
    //digitalWrite(bathroomFan, !bbathroomLight);
    if (bbathroomLight == OFF)
    {
      if (bathroomTimer != 0)
      {
        myTimer.stop(bathroomTimer);
        bathroomTimer = 0;
      }
      //bathroomTimer = myTimer.oscillate(bathroomFan, 5 * SECS_PER_MIN, !bbathroomLight);
      Serial.println("bathroomFan timer=ON");
      bathroomTimer = myTimer.after(1 * myMINUTE, &BathRoomFanOFF);
    }
    else
    {
      myTimer.stop(bathroomTimer);
      bathroomTimer = 0;
      digitalWrite(bathroomFan, ON);
      Serial.println("bathroomFan=ON");
    }
  }
  if (hButton.event_click_Db(2) == 1) //only lights
  {
    Serial.println("bathroomSW0_db");
    bbathroomLight = !digitalRead(bathroomLight);
    Serial.println(bbathroomLight);
    digitalWrite(bathroomLight, bbathroomLight);
    digitalWrite(bathroomBrace, bbathroomLight);
    digitalWrite(bathroomFan, OFF);
  }
  if (hButton.event_press_short(2) == 1)
  {
    Serial.println("bathroomSW0_short");
  }
  if (hButton.event_press_long(2) == 1) //only fan
  {
    Serial.println("bathroomSW0_long");
    // bbathroomFan = !digitalRead(bathroomFan);
    // if (bbathroomFan == OFF) // если выключен - то включаем таймер на 15 минут
    // {
    //   if (bathroomTimer != 0)
    //   {
    //     myTimer.stop(bathroomTimer);
    //     bathroomTimer = 0;
    //   }
    //   Serial.println("bathroomSW0_long bathroomTimer=ON");
    //   bathroomTimer = myTimer.after(10 * mySECOND, &BathRoomFanOFF);
    // }
    // else // Если fan - включен, то выключаем
    // {
    //   Serial.println("bathroomSW0_long bathroomFan=OFF");
    //   digitalWrite(bathroomFan, OFF);
    //   myTimer.stop(bathroomTimer);
    //   bathroomTimer = 0;
    // }
  }
#pragma endregion

#pragma region WC
  if (hButton.event_click_Dn(3) == 1)
  {
    Serial.println("WCSW0");
    bwcLight = !digitalRead(wcLight);
    Serial.println(bwcLight);
    digitalWrite(wcLight, bwcLight);
    digitalWrite(wcBrace, bwcLight);
    //digitalWrite(wcFan, !bwcLight);
    if (bwcLight == OFF)
    {
      if (wcTimer != 0)
      {
        myTimer.stop(wcTimer);
        wcTimer = 0;
      }
      //bathroomTimer = myTimer.oscillate(bathroomFan, 5 * SECS_PER_MIN, !bbathroomLight);
      Serial.println("wcFan timer=ON");
      wcTimer = myTimer.after(1 * myMINUTE, &WCFanOFF);
    }
    else
    {
      myTimer.stop(wcTimer);
      wcTimer = 0;
      digitalWrite(wcFan, ON);
      Serial.println("wcFan=ON");
    }
  }
  if (hButton.event_click_Db(3) == 1)
  {
    Serial.println("WCSW0_db");
    bwcLight = !digitalRead(wcLight);
    Serial.println(bwcLight);
    digitalWrite(wcLight, bwcLight);
    digitalWrite(wcBrace, bwcLight);
    digitalWrite(wcFan, bwcLight);
  }
  if (hButton.event_press_short(3) == 1)
  {

  }
  if (hButton.event_press_long(3) == 1)
  {
    Serial.println("WCSW0_long");
  }
#pragma endregion

#pragma region kitchen
#pragma region kitchenSW0_0
  if (hButton.event_click_Dn(4) == 1)
  {
    Serial.println("kitchenSW0_0");
    bkitchenLight = digitalRead(kitchenLight);
    digitalWrite(kitchenLight, !bkitchenLight);
    digitalWrite(kitchenLightDots, !bkitchenLight); //TODO сейчас не работает основной, убрать когда заработает
  }
  if (hButton.event_click_Db(4) == 1)
  {
    bkitchenLight = digitalRead(kitchenLight);

    digitalWrite(kitchenLight, !bkitchenLight);
    digitalWrite(kitchenLightDots, !bkitchenLight);
    digitalWrite(kitchenLight1, !bkitchenLight);
    digitalWrite(kitchenLight2, !bkitchenLight);
    
  }
  if (hButton.event_press_short(4) == 1)
  {
  }
  if (hButton.event_press_long(4) == 1)
  {
    digitalWrite(kitchenLight, OFF);
    digitalWrite(kitchenLightDots, OFF);
    digitalWrite(kitchenLight1, OFF);
    digitalWrite(kitchenLight2, OFF);
    digitalWrite(balconyLight, OFF);
  }
#pragma endregion

#pragma region kitchenSW0_1
  if (hButton.event_click_Dn(5) == 1)
  {
    Serial.println("kitchenSW0_1");

    bkitchenLightDots = digitalRead(kitchenLightDots);
    digitalWrite(kitchenLightDots, !bkitchenLightDots);
  }
  if (hButton.event_click_Db(5) == 1)
  {
    bbalconyLight = digitalRead(balconyLight);
    digitalWrite(balconyLight, !balconyLight);
  }
  if (hButton.event_press_short(5) == 1)
  {
  }
  if (hButton.event_press_long(5) == 1)
  {
  }
#pragma endregion

#pragma region kitchenSW1_0
  if (hButton.event_click_Dn(6) == 1)
  {
    Serial.println("kitchenSW1_0");
    bkitchenLight1 = digitalRead(kitchenLight1);
    digitalWrite(kitchenLight1, !bkitchenLight1);
    digitalWrite(kitchenLight2, !bkitchenLight1);
  }
  if (hButton.event_click_Db(6) == 1)
  {
  }
  if (hButton.event_press_short(6) == 1)
  {
  }
  if (hButton.event_press_long(6) == 1)
  {
  }
#pragma endregion
#pragma endregion

#pragma region balconySW0
  if (hButton.event_click_Dn(7) == 1)
  {
    Serial.println("balconySW0");

    bbalconyLight = digitalRead(balconyLight);
    digitalWrite(balconyLight, !bbalconyLight);
  }
  if (hButton.event_click_Db(7) == 1)
  {
  }
  if (hButton.event_press_short(7) == 1)
  {
  }
  if (hButton.event_press_long(7) == 1)
  {
  }
#pragma endregion

#pragma region livingRoom
#pragma region livingRoomSW0
  if (hButton.event_click_Dn(8) == 1)
  {
    Serial.println("livingRoomSW0");
    blivingRoomLight = digitalRead(livingRoomLight);
    digitalWrite(livingRoomLight, !blivingRoomLight);
  }
  if (hButton.event_click_Db(8) == 1)
  {
  }
  if (hButton.event_press_short(8) == 1)
  {
  }
  if (hButton.event_press_long(8) == 1)
  {
  }
#pragma endregion

#pragma region livingRoomSW1
  if (hButton.event_click_Dn(9) == 1)
  {
    Serial.println("livingRoomSW1");
    blivingRoomBrace = digitalRead(livingRoomBrace);
    digitalWrite(livingRoomBrace, !blivingRoomBrace);
  }
  if (hButton.event_click_Db(9) == 1)
  {
    
  }
  if (hButton.event_press_short(9) == 1)
  {
  }
  if (hButton.event_press_long(9) == 1)
  {
  }
#pragma endregion

#pragma endregion

#pragma region bedRoom
#pragma region bedRoomSW0_0
  if (hButton.event_click_Dn(10) == 1)
  {
    Serial.println("bedRoomSW0_0");
    bbedRoomLight = digitalRead(bedRoomLight);
    digitalWrite(bedRoomLight, !bbedRoomLight);
    digitalWrite(bedRoomBrace0, !bbedRoomLight);
    digitalWrite(bedRoomBrace1, !bbedRoomLight);
  }
  if (hButton.event_click_Db(10) == 1)
  {
    bbedRoomLight = digitalRead(bedRoomLight);
    digitalWrite(bedRoomLight, !bbedRoomLight);
  }
  if (hButton.event_press_short(10) == 1)
  {
  }
  if (hButton.event_press_long(10) == 1)
  {
  }
#pragma endregion

#pragma region bedRoomSW0_1
  if (hButton.event_click_Dn(11) == 1)
  {
    Serial.println("bedRoomSW0_1");
    bhallLight = digitalRead(hallLight);
    digitalWrite(hallLight, !bhallLight);
  }
  if (hButton.event_click_Db(11) == 1)
  {
  }
  if (hButton.event_press_short(11) == 1)
  {
  }
  if (hButton.event_press_long(11) == 1)
  {
  }
#pragma endregion

#pragma region bedRoomSW1_0
  if (hButton.event_click_Dn(12) == 1)
  {
    Serial.println("bedRoomSW1_0");
    bbedRoomBrace0 = digitalRead(bedRoomBrace0);
    digitalWrite(bedRoomBrace0, !bbedRoomBrace0);
  }
  if (hButton.event_click_Db(12) == 1)
  {
  }
  if (hButton.event_press_short(12) == 1)
  {
  }
  if (hButton.event_press_long(12) == 1)
  {
  }
#pragma endregion
#pragma region bedRoomSW1_1
  if (hButton.event_click_Dn(13) == 1)
  {
    Serial.println("bedRoomSW1_1");
    bbedRoomBrace0 = digitalRead(bedRoomBrace0);
    digitalWrite(bedRoomBrace0, !bbedRoomBrace0);
  }
  if (hButton.event_click_Db(13) == 1)
  {
  }
  if (hButton.event_press_short(13) == 1)
  {
  }
  if (hButton.event_press_long(13) == 1)
  {
  }
#pragma endregion
#pragma region bedRoomSW2_1
  if (hButton.event_click_Dn(14) == 1)
  {
    Serial.println("bedRoomSW2_1");
    bbedRoomBrace1 = digitalRead(bedRoomBrace1);
    digitalWrite(bedRoomBrace1, !bbedRoomBrace1);
  }
  if (hButton.event_click_Db(14) == 1)
  {
  }
  if (hButton.event_press_short(14) == 1)
  {
  }
  if (hButton.event_press_long(14) == 1)
  {
  }
#pragma endregion
#pragma region bedRoomSW2_2
  if (hButton.event_click_Dn(15) == 1)
  {
    Serial.println("bedRoomSW2_2");
    bbedRoomBrace1 = digitalRead(bedRoomBrace1);
    digitalWrite(bedRoomBrace1, !bbedRoomBrace1);
  }
  if (hButton.event_click_Db(15) == 1)
  {
  }
  if (hButton.event_press_short(15) == 1)
  {
  }
  if (hButton.event_press_long(15) == 1)
  {
  }
#pragma endregion

#pragma endregion

#pragma region childRoom
#pragma region childRoomSW0_0
  if (hButton.event_click_Dn(16) == 1)
  {
    Serial.println("childRoomSW0_0");
    bchildRoomLight = digitalRead(childRoomLight);
    digitalWrite(childRoomLight, !bchildRoomLight);
  }
  if (hButton.event_click_Db(16) == 1)
  {
    bchildRoomLight = !digitalRead(childRoomLight);
    digitalWrite(childRoomLight, bchildRoomLight);
    digitalWrite(childRoomBrace, bchildRoomLight);
    
    digitalWrite(hallLight, bchildRoomLight); 
    
  }
  if (hButton.event_press_short(16) == 1)
  {
  }
  if (hButton.event_press_long(16) == 1)
  {
    digitalWrite(childRoomLight, OFF2);
    digitalWrite(childRoomBrace, OFF2);
    
  }
#pragma endregion

//#pragma region childRoomSW0_1
//  if (hButton.event_click_Dn(17) == 1)
//  {
//    Serial.println("childRoomSW0_1");
//    bchildRoomLight = digitalRead(childRoomLight);
//    digitalWrite(childRoomLight, !bchildRoomLight);
//    digitalWrite(childRoomBrace, !bchildRoomLight);
//    //bchildRoomLight = !bchildRoomLight;
//    //digitalWrite(childRoomLight, bchildRoomLight);
//  }
//  if (hButton.event_click_Db(17) == 1)
//  {
//  }
//  if (hButton.event_press_short(17) == 1)
//  {
//  }
//  if (hButton.event_press_long(17) == 1)
//  {
 // }
//#pragma endregion

#pragma region childRoomSW1_0
  if (hButton.event_click_Dn(17) == 1)
  {
    Serial.println("childRoomSW1_0_Dn");
    bchildRoomBrace = digitalRead(childRoomBrace);
    digitalWrite(childRoomBrace, !bchildRoomBrace);
  }
  if (hButton.event_click_Db(17) == 1)
  {
    Serial.println("childRoomSW1_0_db");
    bchildRoomBrace = digitalRead(childRoomBrace);
    digitalWrite(childRoomBrace, !bchildRoomBrace);
    digitalWrite(childRoomLight, !bchildRoomBrace);
  }
  if (hButton.event_press_short(17) == 1)
  {
  }
  if (hButton.event_press_long(17) == 1)
  {
    digitalWrite(childRoomLight, OFF2);
    digitalWrite(childRoomBrace, OFF2);
  }
#pragma endregion
//#pragma region childRoomSW1_1
//  if (hButton.event_click_Dn(19) == 1)
//  {
//    Serial.println("childRoomSW1_1");
//    bchildRoomLight = digitalRead(childRoomLight);
//    digitalWrite(childRoomLight, !bchildRoomLight);
//    //bchildRoomLight = !bchildRoomLight;
//    //digitalWrite(childRoomLight, bchildRoomLight);
//  }
//  if (hButton.event_click_Db(19) == 1)
//  {
//  }
//  if (hButton.event_press_short(19) == 1)
//  {
//  }
//  if (hButton.event_press_long(19) == 1)
//  {
//  }
#pragma endregion

#pragma endregion

  if (hButton.event_click_Dn() == 1) // - событие нажатия                          кнопки
  {
    //Serial.println("all event_click_Dn");
  }
  if (hButton.event_click_Db() == 1) // - событие двойного щелчка                  кнопки
  {
  }
  if (hButton.event_press_short() == 1) // - событие короткого нажатия                кнопки
  {
  }
  if (hButton.event_press_long() == 1) // - событие длинного  нажатия                кнопки
  {
  }
  if (hButton.event_click_Up() == 1)
  {
    //Serial.println("all event_click_Up");
  }
}
