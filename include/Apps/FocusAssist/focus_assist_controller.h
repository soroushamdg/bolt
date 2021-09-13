#include <Arduino.h>

enum class FocusAssistMode
{
    fa_focus,
    fa_break,
    fa_idle,
};

class FocusAssistController
{
private:
    static uint16_t count;
    hw_timer_t *timer = NULL;

public:
    static FocusAssistMode assistMode;

    uint8_t handler_interval_time = 500;

    static uint16_t focusTimeSec;
    static uint16_t breakTimeSec;

    TaskHandle_t _backgroundHandle = NULL;

    void *handler_parameters;
    FocusAssistController(void (*_handler)(void *parameters), void *parameter)
    {
        assistMode = FocusAssistMode::fa_idle;
        handler_parameters = parameter;
        handler = _handler;
    }
    static void onTimerInterrupt()
    {
        count++;
        if (count == focusTimeSec && assistMode == FocusAssistMode::fa_focus)
        {
            count = 0;
            assistMode = FocusAssistMode::fa_break;
        }
        else if (count == breakTimeSec && assistMode == FocusAssistMode::fa_break)
        {
            count = 0;
            assistMode = FocusAssistMode::fa_focus;
        }
        else
        {
            return;
        }
    }

    void setFocusTimeSecs(uint16_t focus_time)
    {
        focusTimeSec = focus_time;
    }

    uint16_t getFocusTime()
    {
        return focusTimeSec;
    }

    void setBreakTimeSecs(uint16_t break_time)
    {
        breakTimeSec = break_time;
    }

    uint16_t getBreakTime()
    {
        return breakTimeSec;
    }

    //Used to check if it's ready to work.
    bool hasFocusBreakTimes()
    {
        return (breakTimeSec != 0) && (focusTimeSec != 0) && (handler_interval_time != 0);
    }

    void startTimer()
    {
        timer = timerBegin(0, 80, true);
        count = 0;
        assistMode = FocusAssistMode::fa_focus;
        // Attach interupt function to timer.
        timerAttachInterrupt(timer, &onTimerInterrupt, true);
        enableHandlerTask();
    }

    void pauseTimer()
    {
        timerStop(timer);
    }

    void resumeTimer()
    {
        timer = timerBegin(0, 80, true);
        // Attach interupt function to timer.
        timerAttachInterrupt(timer, &onTimerInterrupt, true);
        enableHandlerTask();
    }

    void stopTimer()
    {
        timerStop(timer);
        count = 0;
        assistMode = FocusAssistMode::fa_idle;
        disableHandlerTask();
    }

    void resetTimer()
    {
        count = 0;
    }

    uint16_t getTimerCount()
    {
        return count;
    }

    void (*handler)(void *parameters);

    /*
        Runs in background when timer is running and will run a function on specific interval(for example every 60 seconds.)
    */
    void _background()
    {
        for (;;)
        {
            handler(handler_parameters);
        }
        vTaskDelay(handler_interval_time / portTICK_PERIOD_MS);
    }

    static void FocusAssistController::static_Background(void *pvParameter)
    {
        FocusAssistController *fac = static_cast<FocusAssistController *>(pvParameter); //obtain the instance pointer
        fac->_background();                                                             //dispatch to the member function, now that we have an instance pointer
    }

    void enableHandlerTask()
    {
        xTaskCreate(static_Background,
                    "Focus Assist Background Task",
                    configMINIMAL_STACK_SIZE,
                    this,
                    3,
                    &_backgroundHandle);
    }

    void disableHandlerTask()
    {
        vTaskSuspend(_backgroundHandle);
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