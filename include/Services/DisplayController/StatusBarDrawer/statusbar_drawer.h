#include <Arduino.h>
#include "math.h"
#include "statusbar_icons.h"

class StatusBarDrawer
{
private:
    // Clear a square at x:113 to x:127 and Y:0 to y:15
    void clear_alarm_icon_placeholder()
    {
        for (int x = 113; x < 128; x++)
        {
            for (int y = 0; y < 16; y++)
            {
                display.writePixel(x, y, 0);
            }
        }
        display.display();
    }

    // Clear a square at x:91 to x:105 and Y:0 to y:15
    void clear_wireless_icon_placeholder()
    {
        for (int x = 96; x < 106; x++)
        {
            for (int y = 0; y < 16; y++)
            {
                display.writePixel(x, y, 0);
            }
        }
        display.display();
    }

    // Clear a square at x:0 to x:15 and Y:0 to y:15
    void clear_bluetooth_icon_placeholder()
    {
        for (int x = 81; x < 15; x++)
        {
            for (int y = 0; y < 16; y++)
            {
                display.writePixel(x, y, 0);
            }
        }
        display.display();
    }

    void clear_message_area()
    {

        display.clearDisplayArea(0, 0, 80, 15);
    }

public:
    StatusBarDrawer() {}

    // Draw a icon at x:113 to x:127 and Y:0 to y:15
    void DrawAlarmIcon()
    {
        clear_alarm_icon_placeholder();
        display.drawBitmap(113, 0, status_icon_alarm, 15, 15, 1);
        display.display();
        return;
    }

    // Remove a icon at x:113 to x:127 and Y:0 to y:15
    void RemoveAlarmIcon()
    {
        clear_alarm_icon_placeholder();
        return;
    }

    // Draw a icon at x:91 to x:105 and Y:0 to y:15
    void DrawWirelessIcon()
    {
        clear_wireless_icon_placeholder();
        display.drawBitmap(96, 0, status_icon_wifi, 15, 15, 1);
        display.display();
        return;
    }

    // Remove a icon at x:91 to x:105 and Y:0 to y:15
    void RemoveWirelessIcon()
    {
        clear_wireless_icon_placeholder();

        return;
    }

    // Draw a icon at x:91 to x:105 and Y:0 to y:15
    void DrawBluetoothIcon()
    {
        clear_bluetooth_icon_placeholder();
        display.drawBitmap(81, 0, status_icon_bluetooth, 15, 15, 1);
        display.display();
        return;
    }

    // Remove a icon at x:91 to x:105 and Y:0 to y:15
    void RemoveBluetoothIcon()
    {
        clear_bluetooth_icon_placeholder();

        return;
    }

    // Write 2 line message on top corner left.
    void WriteTwoLevelMessage(String line1, String line2)
    {
        display.setFont();
        clear_message_area();
        display.setTextSize(1);  // Normal 1:1 pixel scale
        display.setTextColor(1); // Draw white text
        display.setCursor(0, 0); // Start at top-left corner
        display.println(line1);
        display.println(line2);
        display.display();
        display.setFont(&montserrat_05pt7b);
    }

    void WriteOneLevelMessage(String message)
    {
        clear_message_area();
        display.setTextSize(2);  // Normal 1:1 pixel scale
        display.setTextColor(1); // Draw white text
        display.setCursor(0, 0); // Start at top-left corner
        display.println(message);
        display.display();
    }
};
