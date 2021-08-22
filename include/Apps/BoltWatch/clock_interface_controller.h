#include <Arduino.h>
#include <Apps/BoltWatch/watchfaces/clock_face_analog.h>
#include <Apps/BoltWatch/watchfaces/clock_face_digital.h>

enum ClockfaceMode
{
    digital,
    analog
};

class ClockInterfaceController
{
private:
    ClockfaceMode clockface_mode;
    // TODO : ADD TIME CONTROLLER OBJECT TO GET LATEST TIME.
    // TimeController time_controller;
    void _drawAnalogClock(){
        // TimeController.getCurrentTime();
        // cio_draw_background();
        // cio_draw_hands(hour, minute);
    };

    void _drawDigitalClock(){
        // TimeController.getCurrentTime();
        // cid_draw_background();
        // cid_draw_digits(hour, minute, second, draw_second, Font_16x26, 16, 26);
    };

public:
    ClockInterfaceController(ClockfaceMode clockfacemode)
    {
        clockface_mode = clockfacemode;
    }

    void updateScreen(void)
    {
        switch (clockface_mode)
        {
        case digital:
            _drawDigitalClock();
            break;
        case analog:
            _drawAnalogClock();
            break;
        default:
            break;
        }
    }
};
