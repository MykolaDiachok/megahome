#include "TimeConstants.h"

class PowerDevice
{
private:
    int pin;    // GPIO pin connected to the light
    bool state; // Current state of the light (true for ON, false for OFF)
    unsigned long offTimestamp = 0;

public:
    PowerDevice(int pin) : pin(pin), state(false)
    {
        pinMode(pin, OUTPUT); // Set the pin as an output
        off();                // Ensure the light starts in the OFF state
    }

    void on()
    {
        state = true;
        digitalWrite(pin, ON); // Turn the light on
    }

    void off()
    {
        state = false;
        digitalWrite(pin, OFF); // Turn the light off
    }

    void toggle()
    {
        state ? off() : on(); // Toggle the state of the light
    }

    bool isOn() const
    {
        return state; // Return the current state
    }

    void setState(bool newState)
    {
        state = newState;
        digitalWrite(pin, newState ? HIGH : LOW);
    }

    void scheduleOff(unsigned long duration)
    {
        offTimestamp = millis() + duration;
    }

    void scheduleOffMinutes(unsigned int minutes)
    {
        scheduleOff(minutes * MINUTE);
    }

    void scheduleOffSeconds(unsigned int seconds)
    {
        scheduleOff(seconds * SECOND);
    }

    // Call this function regularly to check if it's time to turn off the device
    void checkOffSchedule()
    {
        if (offTimestamp != 0 && millis() >= offTimestamp)
        {
            off();
            offTimestamp = 0; // Reset schedule
        }
    }
};
