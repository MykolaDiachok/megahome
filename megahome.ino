#include "Button.h"
#include "Timer.h"
#include "MainConstants.h"
#include "TimeConstants.h"
#include "PowerDevice.h"

Timer myTimer;

PowerDevice light_hall(PIN_HALL_LIGHT);

int8_t hallTimer = 0; // hallway timer
int8_t allTimer = 0;  // main timer

PowerDevice light_bathroom(PIN_BATHROOM_LIGHT);
PowerDevice fan_bathroom(PIN_BATHROOM_FAN);
PowerDevice light_bathroomBrace(PIN_BATHROOM_BRACE);

PowerDevice light_wc(PIN_WC_LIGHT);
PowerDevice fan_wc(PIN_WC_FAN);
PowerDevice light_wcBrace(PIN_WC_BRACE);

bool bkitchenLight = false;
bool bkitchenLight1 = false;
bool bkitchenLight2 = false;

bool bkitchenLightDots = false;

bool bbalconyLight = false;

bool blivingRoomLight = false;
bool blivingRoomBrace = false;

bool bbedRoomLight = false;
bool bbedRoomBrace0 = false;
bool bbedRoomBrace1 = false;
bool bchildRoomLight = false;
bool bchildRoomBrace = false;

Button hButton;

unsigned long HallTimeOff = 0;

void setup()
{
  Serial.begin(9600);
  // pinMode(inOutDoorSensor, INPUT);
  hButton.NO(); // N.O. Normal Open
  // hButton.NC(); // N.C. Normal Closed
  // hButton.pullUp();
  hButton.pullDn(); // - подтяжка пинов кнопок к GND
  hButton.duration_bounce(50);
  hButton.duration_click_Db(250);
  hButton.duration_inactivity_Up(5000);
  hButton.duration_inactivity_Dn(1000);
  hButton.duration_press(500);
  hButton.button(PIN_HALL_SW0 // 0
                 ,
                 PIN_HALL_SW1 // 1
                 ,
                 PIN_BATHROOM_SW0 // 2
                 ,
                 PIN_WS_SW0 // 3
                 ,
                 kitchenSW0_0 // 4
                 ,
                 kitchenSW0_1 // 5
                 ,
                 kitchenSW1_0 // 6
                 ,
                 balconySW0 // 7
                 ,
                 livingRoomSW0 // 8
                 ,
                 livingRoomSW1 // 9
                 ,
                 bedRoomSW0_0 // 10
                 ,
                 bedRoomSW0_1 // 11
                 ,
                 bedRoomSW1_0 // 12
                 ,
                 bedRoomSW1_1 // 13
                 ,
                 bedRoomSW2_0 // 14
                 ,
                 bedRoomSW2_1 // 15
                 ,
                 childRoomSW0_0 // 16
                 //, childRoomSW0_1  //17
                 ,
                 childRoomSW1_0 // 17
                 // , childRoomSW1_1  //19
                 ,
                 inOutDoorSensor // 18
  );                             // arduino pins connected to button



  // digitalWrite(PIN_WC_LIGHT, LOW);
  pinMode(kitchenLight, OUTPUT);
  digitalWrite(kitchenLight, OFF);

  pinMode(kitchenLight1, OUTPUT);
  digitalWrite(kitchenLight1, OFF);

  pinMode(kitchenLight2, OUTPUT);
  digitalWrite(kitchenLight2, OFF);

  pinMode(kitchenLightDots, OUTPUT);
  digitalWrite(kitchenLightDots, OFF);

  // balconyLight
  pinMode(balconyLight, OUTPUT);
  digitalWrite(balconyLight, OFF);

  pinMode(livingRoomLight, OUTPUT);
  digitalWrite(livingRoomLight, OFF);

  // livingRoomBrace

  pinMode(livingRoomBrace, OUTPUT);
  digitalWrite(livingRoomBrace, OFF);

  pinMode(bedRoomLight, OUTPUT);
  digitalWrite(bedRoomLight, OFF);

  pinMode(bedRoomBrace0, OUTPUT);
  digitalWrite(bedRoomBrace0, OFF);

  pinMode(bedRoomBrace1, OUTPUT);
  digitalWrite(bedRoomBrace1, OFF);

  pinMode(childRoomLight, OUTPUT);
  digitalWrite(childRoomLight, OFF);

  pinMode(childRoomBrace, OUTPUT);
  digitalWrite(childRoomBrace, OFF);
  // put your setup code here, to run once:
}

bool OpenInOutDoorSensor = false;
bool ballOFF = false;

void allOFF(bool withHall = false)
{
  Serial.print("allOFF");
  if (withHall)
  {
    Serial.println(" with hall");
    light_hall.off();
  }
  light_bathroom.off();
  light_bathroomBrace.off();
  fan_bathroom.off();

  light_wc.off();
  light_wcBrace.off();
  fan_wc.off();

  digitalWrite(kitchenLight, OFF);
  digitalWrite(kitchenLight1, OFF);
  digitalWrite(kitchenLight2, OFF);
  digitalWrite(kitchenLightDots, OFF);

  digitalWrite(balconyLight, OFF);

  digitalWrite(livingRoomLight, OFF);
  digitalWrite(livingRoomBrace, OFF);

  digitalWrite(bedRoomLight, OFF);
  digitalWrite(bedRoomBrace0, OFF);
  digitalWrite(bedRoomBrace1, OFF);

  digitalWrite(childRoomLight, OFF);
  digitalWrite(childRoomBrace, OFF);

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
    allTimer = myTimer.after(1 * MINUTE, &allLightsOFF);
  }
  ballOFF = false;
}

void loop()
{
  myTimer.update();
  light_hall.update();

  light_bathroom.update();
  light_bathroomBrace.update();
  fan_bathroom.update();

  light_wc.update();
  light_wcBrace.update();
  fan_wc.update();

  hButton.read();
//
#pragma region OutDoor //TODO needs to be finalized
  if (hButton.event_click_Dn(18) == 1)
  {
    Serial.println("OutDoor event_click_Dn");
    OpenInOutDoorSensor = false;
    if ((light_hall.isOn() == false) && (!ballOFF))
    {
      ballOFF = false;
      Serial.println("start timer hall light off");
      light_hall.scheduleOffMinutes(2);
    }
    else
    {
      ballOFF = false;
      hallTimer = myTimer.after(2 * MINUTE, &allLightsOFF);
    }
  }
  if (hButton.event_click_Up(18) == 1)
  {
    Serial.println("OutDoor event_click_Up");
    light_hall.on();
    OpenInOutDoorSensor = true;
    myTimer.stop(hallTimer);
    hallTimer = 0;
    // ballOFF = false;
  }
#pragma endregion

#pragma region hall
#pragma region hallSW0
  if (hButton.event_click_Dn(0) == 1)
  {
    Serial.println("pinHallSW0");
    light_hall.toggle();
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
    ballOFF = true;
    Serial.println("PIN_HALL_SW1");
    allOFF(false);
  }
  if (hButton.event_click_Db(1) == 1)
  {
    light_hall.toggle();
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
    Serial.println("PIN_BATHROOM_SW0");
    light_bathroom.toggle();
    light_bathroomBrace.setState(light_bathroom.isOn());
    if (light_bathroom.isOn())
    {
      fan_bathroom.on();
    }
    else
    {
      fan_bathroom.scheduleOffMinutes(2);
    }
  }
  if (hButton.event_click_Db(2) == 1) // only lights
  {
    Serial.println("PIN_BATHROOM_SW0_db");
    light_bathroom.toggle();
    light_bathroomBrace.setState(light_bathroom.isOn());
    fan_bathroom.off();
  }
  if (hButton.event_press_short(2) == 1)
  {
    Serial.println("PIN_BATHROOM_SW0_short");
  }
  if (hButton.event_press_long(2) == 1) // only fan
  {
    Serial.println("PIN_BATHROOM_SW0_long");
    fan_bathroom.on();
    fan_bathroom.scheduleOffMinutes(2);
  }
#pragma endregion

#pragma region WC
  if (hButton.event_click_Dn(3) == 1)
  {
    Serial.println("PIN_BATHROOM_SW0");
    light_wc.toggle();
    bool wcIsOn = light_bathroom.isOn();
    light_bathroomBrace.setState(wcIsOn);
    if (wcIsOn)
    {
      fan_wc.on();
    }
    else
    {
      fan_wc.scheduleOffMinutes(2);
    }
    
  }
  if (hButton.event_click_Db(3) == 1)
  {
    light_wc.toggle();
    bool wcIsOn = light_bathroom.isOn();
    light_bathroomBrace.setState(wcIsOn);
    fan_wc.off();
  }
  if (hButton.event_press_short(3) == 1)
  {
  }
  if (hButton.event_press_long(3) == 1)
  {
    Serial.println("PIN_BATHROOM_SW00_long");
    fan_wc.on();
    fan_wc.scheduleOffMinutes(2);
  }
#pragma endregion

#pragma region kitchen
#pragma region kitchenSW0_0
  if (hButton.event_click_Dn(4) == 1)
  {
    Serial.println("kitchenSW0_0");
    bkitchenLight = digitalRead(kitchenLight);
    digitalWrite(kitchenLight, !bkitchenLight);
    digitalWrite(kitchenLightDots, !bkitchenLight); // TODO сейчас не работает основной, убрать когда заработает
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
    light_hall.toggle();
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

    digitalWrite(PIN_HALL_LIGHT, bchildRoomLight);
  }
  if (hButton.event_press_short(16) == 1)
  {
  }
  if (hButton.event_press_long(16) == 1)
  {
    digitalWrite(childRoomLight, OFF);
    digitalWrite(childRoomBrace, OFF);
  }
#pragma endregion

  // #pragma region childRoomSW0_1
  //   if (hButton.event_click_Dn(17) == 1)
  //   {
  //     Serial.println("childRoomSW0_1");
  //     bchildRoomLight = digitalRead(childRoomLight);
  //     digitalWrite(childRoomLight, !bchildRoomLight);
  //     digitalWrite(childRoomBrace, !bchildRoomLight);
  //     //bchildRoomLight = !bchildRoomLight;
  //     //digitalWrite(childRoomLight, bchildRoomLight);
  //   }
  //   if (hButton.event_click_Db(17) == 1)
  //   {
  //   }
  //   if (hButton.event_press_short(17) == 1)
  //   {
  //   }
  //   if (hButton.event_press_long(17) == 1)
  //   {
  //  }
  // #pragma endregion

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
    digitalWrite(childRoomLight, OFF);
    digitalWrite(childRoomBrace, OFF);
  }
#pragma endregion
// #pragma region childRoomSW1_1
//   if (hButton.event_click_Dn(19) == 1)
//   {
//     Serial.println("childRoomSW1_1");
//     bchildRoomLight = digitalRead(childRoomLight);
//     digitalWrite(childRoomLight, !bchildRoomLight);
//     //bchildRoomLight = !bchildRoomLight;
//     //digitalWrite(childRoomLight, bchildRoomLight);
//   }
//   if (hButton.event_click_Db(19) == 1)
//   {
//   }
//   if (hButton.event_press_short(19) == 1)
//   {
//   }
//   if (hButton.event_press_long(19) == 1)
//   {
//   }
#pragma endregion

#pragma endregion

  if (hButton.event_click_Dn() == 1) // - событие нажатия                          кнопки
  {
    // Serial.println("all event_click_Dn");
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
    // Serial.println("all event_click_Up");
  }
}
