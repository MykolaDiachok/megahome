#include "Timer.h"
#include "TimeConstants.h"

class PowerDevice
{
private:
    static PowerDevice *instance;
    int pin;                // GPIO pin connected to the light
    bool state;             // Current state of the light (true for ON, false for OFF)
    Timer timer;            // Timer instance for scheduling the fan to turn off
    int8_t offEventId = -1; // Timer event ID for the scheduled turn-off event, -1 when not scheduled

public:
    PowerDevice(int pin) : pin(pin), state(false)
    {
        pinMode(pin, OUTPUT); // Set the pin as an output
        off();                // Ensure the light starts in the OFF state
        instance = this;
    }

    static void offStatic()
    { // Static method to call off
        if (instance)
        {
            instance->off(); // Call the non-static off method
        }
    }

    void on()
    {
        state = true;
        digitalWrite(pin, ON); // Turn the light on
        cancelScheduledOff();
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
        cancelScheduledOff();
    }

    void scheduleOff(unsigned long duration)
    {
        cancelScheduledOff();                          // Cancel any existing scheduled off event
        offEventId = timer.after(duration, offStatic); // Schedule new off event
    }

    void scheduleOffSeconds(unsigned int seconds)
    {
        scheduleOff(seconds * SECOND);
    }

    void scheduleOffMinutes(unsigned int minutes)
    {
        scheduleOff(minutes * MINUTE);
    }

    void update()
    {
        timer.update(); // Update timer to check for any due events
    }

private:
    void cancelScheduledOff()
    {
        if (offEventId != -1)
        {
            timer.stop(offEventId); // Cancel any existing scheduled off event
            offEventId = -1;
        }
    }
};

// Initialize the static instance pointer
PowerDevice *PowerDevice::instance = nullptr;