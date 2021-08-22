#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class DisplayController
{

public:
    DisplayController()
    {
    }

    void init()
    {
        while (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
        {
            Serial.print(F("SSD1306 allocation failed, Trying again..."));

            delay(1000);
        }
    }

    void clearBlueArea()
    {
        display.clearDisplayArea(0, 16, 128, 48);
    }

    void clearYellowArea()
    {
        display.clearDisplayArea(0, 0, 128, 15);
    }

    void fillBlueArea()
    {
        display.fillRect(0, 16, 128, 48, 1);
    }

    void fillYelloweArea()
    {
        display.fillRect(0, 0, 128, 15, 1);
    }

    void printInCenter(String text, int color, int background, int top_margin)
    {
        display.setCursor(64 - (text.length() * 6 / 2), 36 + top_margin);
        display.setTextColor(color, background);
        display.println(text);
    }

    void writehello()
    {
        display.clearDisplayArea(0, 16, 128, 48);

        display.setTextSize(1);  // Normal 1:1 pixel scale
        display.setTextColor(1); // Draw white text
        display.setCursor(0, 0); // Start at top-left corner
        display.println(F("3:22"));

        display.setTextColor(0, 1); // Draw 'inverse' text
        display.println(F("16 Aug, 2021"));

        display.setTextSize(2); // Draw 2X-scale text
        display.setTextColor(1);
        display.print(F("0x"));
        display.println(0xDEADBEEF, HEX);
        display.println(0xDEADB231, HEX);
        display.println(0xDEADBE43, HEX);
        display.println(0xDEA423EF, HEX);
        display.println(0xDE23BEEF, HEX);
        display.display();
        delay(2000);

        Serial.println(F("Wrote helloWorld and other stuff on display!"));
    }
};