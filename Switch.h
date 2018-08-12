/*
  Released into the public domain.
*/
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

class Switch
{
  public:
    Switch(int pin, int counter);    
    void click_Dn();
    void click_Db();
  private:
    int _pin;
    int _counter;
};

#endif