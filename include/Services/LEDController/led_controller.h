#include <Arduino.h>
#include <analogWrite.h>

class LEDController
{
private:
    uint8_t pin;
    uint8_t defaultvalue;

public:
    LEDController(uint8_t pin_number, uint8_t default_val)
    {
        pin = pin_number;
        pinMode(pin_number, OUTPUT);
        defaultvalue = default_val;
        digitalWrite(pin_number, default_val);
    }

    void high()
    {
        digitalWrite(pin, 1);
    }

    void low()
    {
        digitalWrite(pin, 0);
    }

    void analog(uint8_t value)
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