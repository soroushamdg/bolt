#include <Arduino.h>

class FocusAssistController
{
private:
    static uint8_t count;
    hw_timer_t *timer = NULL;

    static void onTimerInterupt()
    {
        count++;
    }

    uint16_t focusTimeSec = 45 * 60;
    uint16_t breakTimeSec = 15 * 60;

public:
    FocusAssistController() {}

    void setFocusTimeSecs(uint8_t focus_time)
    {
        focusTimeSec = focus_time;
    }

    uint8_t getFocusTime()
    {
        return focusTimeSec;
    }

    void setBreakTimeSecs(uint8_t break_time)
    {
        breakTimeSec = break_time;
    }

    uint8_t getBreakTime()
    {
        return breakTimeSec;
    }

    //Used to check if it's ready to work.
    bool hasFocusBreakTimes()
    {
        return (breakTimeSec != 0) && (focusTimeSec != 0);
    }

    void startTimer()
    {
        timer = timerBegin(0, 80, true);

        // Attach interupt function to timer.
        timerAttachInterrupt(timer, &onTimerInterupt, true);
    }

    void pauseTimer()
    {
        timerStop(timer);
    }

    void stopTimer()
    {
        timerStop(timer);
        count = 0;
    }

    void resetTimer()
    {
        count = 0;
    }

    uint8_t getTimerCount()
    {
        return count;
    }
};

/* 
 void drawBoard()
    {
        oledcontroller.fillBlueArea();
        oledcontroller.printInCenter(" 12:39 ", 2, 1, 0, -8);
        oledcontroller.printInCenter(" Break ", 1, 1, 0, 8);

        display.fillRect(0, 15, 24, 12, 0);
        display.display();
    }
*/