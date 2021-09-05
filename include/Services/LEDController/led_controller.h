#include <Arduino.h>

class LEDController
{
private:
    uint8_t pin;
    uint8_t defaultvalue;
    bool analog;

public:
    LEDController(uint8_t pin_number, uint8_t default_val, bool analog)
    {
        pin = pin_number;
        pinMode(pin_number, OUTPUT);
        defaultvalue = default_val;
        digitalWrite(pin_number, default_val);
        analog = analog;
    }

    void pinhigh()
    {
        digitalWrite(pin, 1);
    }

    void pinlow()
    {
        digitalWrite(pin, 0);
    }

    void pinanalog(uint8_t value)
    {
        if (value >= 0 && value <= 255)
        {
            analogWrite(pin, value);
        }
    }
};

class RGBLEDController
{
private:
public:
};