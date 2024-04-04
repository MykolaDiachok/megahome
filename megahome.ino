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

PowerDevice light_kitchen0(PIN_KITCHEN_LIGHT0);
PowerDevice light_kitchen1(PIN_KITCHEN_LIGHT1);
PowerDevice light_kitchen2(PIN_KITCHEN_LIGHT2);
PowerDevice light_kitchen_dots(PIN_KITCHEN_LIGHT_DOTS);

PowerDevice light_balcony(PIN_BALCONY_LIGHT);

PowerDevice light_livingRoom(PIN_LIVINGROOM_LIGHT);
PowerDevice light_livingRoomBrace(PIN_LIVINGROOM_BRACE);

PowerDevice light_bedRoom(PIN_BEDROOM_LIGHT);
PowerDevice light_bedRoomBrace0(PIN_BEDROOM_BRACE0);
PowerDevice light_bedRoomBrace1(PIN_BEDROOM_BRACE1);

PowerDevice light_childRoom(PIN_CHILDROOM_LIGHT);
PowerDevice light_childRoomBrace(PIN_CHILDROOM_BRACE);

Button hButton;

unsigned long HallTimeOff = 0;

void setup()
{
  Serial.begin(9600);
  
  // pinMode(PIN_OUTER_DOOR_SENSOR, INPUT);
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
                 PIN_KITCHEN_SW0_0 // 4
                 ,
                 PIN_KITCHEN_SW0_1 // 5
                 ,
                 PIN_KITCHEN_SW1_0 // 6
                 ,
                 PIN_BALCONY_SW0 // 7
                 ,
                 PIN_LIVINGRROOM_SW0 // 8
                 ,
                 PIN_LIVINGRROOM_SW1 // 9
                 ,
                 PIN_BEDROOM_SW0_0 // 10
                 ,
                 PIN_BEDROOM_SW0_1 // 11
                 ,
                 PIN_BEDROOM_SW1_0 // 12
                 ,
                 PIN_BEDROOM_SW1_1 // 13
                 ,
                 PIN_BEDROOM_SW2_0 // 14
                 ,
                 PIN_BEDROOM_SW2_1 // 15
                 ,
                 PIN_CHILDROOM_SW0_0 // 16
                 //, childRoomSW0_1  //17
                 ,
                 PIN_CHILDROOM_SW1_0 // 17
                 // , childRoomSW1_1  //19
                 ,
                 PIN_OUTER_DOOR_SENSOR // 18
  );                                   // arduino pins connected to button
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

  light_kitchen0.off();
  light_kitchen1.off();
  light_kitchen2.off();
  light_kitchen_dots.off();

  light_balcony.off();

  light_livingRoom.off();
  light_livingRoomBrace.off();

  light_bedRoom.off();
  light_bedRoomBrace0.off();
  light_bedRoomBrace1.off();

  light_childRoom.off();
  light_childRoomBrace.off();
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

  light_hall.checkOffSchedule();

  light_bathroom.checkOffSchedule();
  light_bathroomBrace.checkOffSchedule();
  fan_bathroom.checkOffSchedule();

  light_wc.checkOffSchedule();
  light_wcBrace.checkOffSchedule();
  fan_wc.checkOffSchedule();

  light_kitchen0.checkOffSchedule();
  light_kitchen1.checkOffSchedule();
  light_kitchen2.checkOffSchedule();
  light_kitchen_dots.checkOffSchedule();

  light_balcony.checkOffSchedule();

  light_livingRoom.checkOffSchedule();
  light_livingRoomBrace.checkOffSchedule();

  light_bedRoom.checkOffSchedule();
  light_bedRoomBrace0.checkOffSchedule();
  light_bedRoomBrace1.checkOffSchedule();

  light_childRoom.checkOffSchedule();
  light_childRoomBrace.checkOffSchedule();

  hButton.read();
//
#pragma region OutDoor //TODO needs to be finalized
  if (hButton.event_click_Dn(18) == 1)
  {
    Serial.println("PIN_OUTER_DOOR_SENSOR event_click_Dn");
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
#pragma region PIN_HALL_SW0
  if (hButton.event_click_Dn(0) == 1)
  {
    Serial.println("PIN_HALL_SW0");
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

#pragma region PIN_HALL_SW1
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
    Serial.println("PIN_WC_SW0");
    light_wc.toggle();
    bool wcIsOn = light_wc.isOn();
    light_wcBrace.setState(wcIsOn);
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
    bool wcIsOn = light_wc.isOn();
    light_wcBrace.setState(wcIsOn);
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
#pragma region PIN_KITCHEN_SW0_0
  if (hButton.event_click_Dn(4) == 1)
  {
    Serial.println("PIN_KITCHEN_SW0_0");
    light_kitchen0.toggle();
  }
  if (hButton.event_click_Db(4) == 1)
  {
  }
  if (hButton.event_press_short(4) == 1)
  {
  }
  if (hButton.event_press_long(4) == 1)
  {
    light_kitchen0.off();
    light_kitchen1.off();
    light_kitchen2.off();
    light_kitchen_dots.off();
    light_balcony.off();
    light_hall.on();
  }
#pragma endregion

#pragma region PIN_KITCHEN_SW0_1
  if (hButton.event_click_Dn(5) == 1)
  {
    Serial.println("PIN_KITCHEN_SW0_1");
    light_kitchen_dots.toggle();
  }
  if (hButton.event_click_Db(5) == 1)
  {
  }
  if (hButton.event_press_short(5) == 1)
  {
  }
  if (hButton.event_press_long(5) == 1)
  {
  }
#pragma endregion

#pragma region PIN_KITCHEN_SW1_0
  if (hButton.event_click_Dn(6) == 1)
  {
    Serial.println("PIN_KITCHEN_SW1_0");
    light_kitchen1.toggle();
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

#pragma region PIN_BALCONY_SW0
  if (hButton.event_click_Dn(7) == 1)
  {
    Serial.println("PIN_BALCONY_SW0");
    light_balcony.toggle();
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
    Serial.println("PIN_LIVINGRROOM_SW0");
    light_livingRoom.toggle();
  }
  if (hButton.event_click_Db(8) == 1)
  {
  }
  if (hButton.event_press_short(8) == 1)
  {
  }
  if (hButton.event_press_long(8) == 1)
  {
    light_livingRoom.off();
    light_livingRoomBrace.off();
    light_hall.on();
  }
#pragma endregion

#pragma region PIN_LIVINGRROOM_SW1
  if (hButton.event_click_Dn(9) == 1)
  {
    Serial.println("PIN_LIVINGRROOM_SW1");
    light_livingRoomBrace.toggle();
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
#pragma region PIN_BEDROOM_SW0_0
  if (hButton.event_click_Dn(10) == 1)
  {
    Serial.println("PIN_BEDROOM_SW0_0");
    light_bedRoom.toggle();
  }
  if (hButton.event_click_Db(10) == 1)
  {
  }
  if (hButton.event_press_short(10) == 1)
  {
  }
  if (hButton.event_press_long(10) == 1)
  {
    light_bedRoom.off();
    light_bedRoomBrace0.off();
    light_bedRoomBrace1.off();
  }
#pragma endregion

#pragma region PIN_BEDROOM_SW0_1
  if (hButton.event_click_Dn(11) == 1)
  {
    Serial.println("PIN_BEDROOM_SW0_1");
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
    light_bedRoom.off();
    light_bedRoomBrace0.off();
    light_bedRoomBrace1.off();
    light_hall.on();
  }
#pragma endregion

#pragma region PIN_BEDROOM_SW1_0
  if (hButton.event_click_Dn(12) == 1)
  {
    Serial.println("PIN_BEDROOM_SW1_0");
    light_bedRoomBrace0.toggle();
  }
  if (hButton.event_click_Db(12) == 1)
  {
  }
  if (hButton.event_press_short(12) == 1)
  {
  }
  if (hButton.event_press_long(12) == 1)
  {
    light_bedRoomBrace0.off();
    light_bedRoom.off();
    light_hall.off();
  }
#pragma endregion
#pragma region PIN_BEDROOM_SW1_1
  if (hButton.event_click_Dn(13) == 1)
  {
    Serial.println("PIN_BEDROOM_SW1_1");
    light_hall.toggle();
  }
  if (hButton.event_click_Db(13) == 1)
  {
    light_bedRoom.toggle();
  }
  if (hButton.event_press_short(13) == 1)
  {
  }
  if (hButton.event_press_long(13) == 1)
  {
    light_hall.scheduleOffSeconds(10);
    light_bedRoom.scheduleOffSeconds(20);
    light_bedRoomBrace0.scheduleOffSeconds(25);
    light_bedRoomBrace0.scheduleOffSeconds(30);
  }
#pragma endregion

#pragma region PIN_BEDROOM_SW2_1
  if (hButton.event_click_Dn(14) == 1)
  {
    Serial.println("PIN_BEDROOM_SW2_1");
    light_bedRoomBrace1.toggle();
  }
  if (hButton.event_click_Db(14) == 1)
  {
  }
  if (hButton.event_press_short(14) == 1)
  {
  }
  if (hButton.event_press_long(14) == 1)
  {
    light_bedRoomBrace0.off();
    light_bedRoom.off();
    light_hall.off();
  }
#pragma endregion
#pragma region bedRoomSW2_2
  if (hButton.event_click_Dn(15) == 1)
  {
    Serial.println("bedRoomSW2_2");
    light_hall.toggle();
  }
  if (hButton.event_click_Db(15) == 1)
  {
    light_bedRoom.toggle();
  }
  if (hButton.event_press_short(15) == 1)
  {
  }
  if (hButton.event_press_long(15) == 1)
  {
    light_hall.scheduleOffSeconds(10);
    light_bedRoom.scheduleOffSeconds(20);
    light_bedRoomBrace0.scheduleOffSeconds(25);
    light_bedRoomBrace0.scheduleOffSeconds(30);
  }
#pragma endregion

#pragma endregion

#pragma region childRoom
#pragma region PIN_CHILDROOM_SW0_0
  if (hButton.event_click_Dn(16) == 1)
  {
    Serial.println("PIN_CHILDROOM_SW0_0");
    light_childRoom.toggle();
  }
  if (hButton.event_click_Db(16) == 1)
  {
    light_hall.toggle();
  }
  if (hButton.event_press_short(16) == 1)
  {
  }
  if (hButton.event_press_long(16) == 1)
  {
    light_childRoom.off();
    light_childRoomBrace.off();
    light_hall.on();
  }
#pragma endregion

#pragma region PIN_CHILDROOM_SW1_0
  if (hButton.event_click_Dn(17) == 1)
  {
    Serial.println("PIN_CHILDROOM_SW1_0");
    light_childRoomBrace.toggle();
  }
  if (hButton.event_click_Db(17) == 1)
  {
    Serial.println("PIN_CHILDROOM_SW1_0_db");
    light_childRoomBrace.toggle();
    if (light_childRoom.isOn())
    {
      light_childRoom.scheduleOffSeconds(30);
    }
  }
  if (hButton.event_press_short(17) == 1)
  {
  }
  if (hButton.event_press_long(17) == 1)
  {
    light_childRoom.off();
    light_childRoomBrace.scheduleOffSeconds(30);
    light_hall.off();
  }
#pragma endregion
#pragma endregion

#pragma endregion

  if (hButton.event_click_Dn() == 1)
  {
    // Serial.println("all event_click_Dn");
  }
  if (hButton.event_click_Db() == 1)
  {
  }
  if (hButton.event_press_short() == 1)
  {
  }
  if (hButton.event_press_long() == 1)
  {
  }
  if (hButton.event_click_Up() == 1)
  {
    // Serial.println("all event_click_Up");
  }
}
