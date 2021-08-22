#include <Arduino.h>

class ClockfaceMiniStatusbar
{
private:
    void clear_statusbar_clock_area(void)
    {
        display.clearDisplayArea(0, 0, 80, 15);
    }

    void draw_time_digits(int hour, int minute)
    {
        // char shour[2];
        // char sminute[2];

        display.setTextSize(1);  // Normal 1:1 pixel scale
        display.setTextColor(1); // Draw white text
        display.setCursor(0, 0); // Start at top-left corner
        display.print(hour);
        display.print(":");

        // sprintf(sminute, "%2d", minute);
        if (minute < 10)
        {
            display.print(F("0"));
        }
        display.print(minute);
    }

    void draw_date(String date)
    {
        display.setCursor(0, 8);
        display.setTextColor(0, 1); // Draw 'inverse' text
        display.println(date);
    }

public:
    ClockfaceMiniStatusbar() {}

    void drawMiniStatus(int hour, int minute, String date)
    {
        clear_statusbar_clock_area();
        draw_time_digits(hour, minute);
        draw_date(date);
        display.display();
    }
};