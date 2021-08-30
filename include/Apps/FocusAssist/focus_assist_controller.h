#include <Arduino.h>

class FocusAssistController
{
private:
    static int count;
    hw_timer_t *timer = NULL;

    static void onTimerInterupt()
    {
        count++;
    }

public:
    FocusAssistController() {}

    void startTimer()
    {
        timer = timerBegin(0, 80, true);

        // Attach interupt function to timer.
        timerAttachInterrupt(timer, &onTimerInterupt, true);
    }

        void drawBoard()
    {
        oledcontroller.fillBlueArea();
        oledcontroller.printInCenter(" 12:39 ", 2, 1, 0, -8);
        oledcontroller.printInCenter(" Break ", 1, 1, 0, 8);

        display.fillRect(0, 15, 24, 12, 0);
        display.display();
    }
};