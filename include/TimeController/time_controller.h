#include <Arduino.h>
#include "RTClib.h"

RTC_DS1307 rtc;

struct Alarm
{
    bool active;
    DateTime time;
};

String months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};

class TimeController
{
private:
    Alarm alarms[3];

    DateTime current_date_time;

public:
    TimeController()
    {
        if (!rtc.begin())
        {
            Serial.println("Couldn't find RTC");
            while (1)
                ;
        }

        if (!rtc.isrunning())
        {
            Serial.println("RTC lost power, lets set the time!");
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }

        current_date_time = rtc.now();
    }

    void setTime(DateTime datetime)
    {
        rtc.adjust(datetime);
    }

    void refreshTime()
    {
        current_date_time = rtc.now();
    }

    DateTime getCurrentDateTime()
    {
        refreshTime();
        return current_date_time;
    }

    String monthName(int month)
    {
        return months[month - 1];
    }
};