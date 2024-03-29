#include "BConstants.h"

class Light {
  private:
    int pin; // GPIO pin connected to the light
    bool state; // Current state of the light (true for ON, false for OFF)
  
  public:
    Light(int pin) : pin(pin), state(false) {
      pinMode(pin, OUTPUT); // Set the pin as an output
      off(); // Ensure the light starts in the OFF state
    }

    void on() {
      state = true;
      digitalWrite(pin, ON); // Turn the light on
    }

    void off() {
      state = false;
      digitalWrite(pin, OFF); // Turn the light off
    }

    void toggle() {
      state ? off() : on(); // Toggle the state of the light
    }

    bool isOn() const {
      return state; // Return the current state
    }
};