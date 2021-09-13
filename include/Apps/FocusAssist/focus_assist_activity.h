#include <Apps/BoltBoard/Activities/activity.h>
#include <Apps/FocusAssist/focus_assist_controller.h>

class FocusAssistActivity : public Activity
{
private:
    FocusAssistController facontroller = FocusAssistController(static_updateScreen, this);
    bool active = false;

public:
    FocusAssistActivity()
    {
        id = "focus_assist_activity";
        setSpecialActivity();
        active = false;
        changeStatusTo(ActivityStatus::created);
    }

    void updateSettings()
    {
        // HERE LOAD SETTINGS AND FOCUS TIME FROM MEMORY - PREFRENCES
    }

    void onCreate() override
    {
        updateSettings();
        facontroller.setFocusTimeSecs(1 * 60); // 1 minute
        facontroller.setFocusTimeSecs(1 * 60);
        if (facontroller.hasFocusBreakTimes())
        {
            return;
        }
    }

    void startFocusAssist()
    {
        facontroller.startTimer();
        active = true;
    }
    void pauseFocusAssist()
    {
        facontroller.pauseTimer();
        active = true;
    }
    void resumeFocusAssist()
    {
        facontroller.startTimer();
        active = true;
    }
    void stopFocusAssist()
    {
        facontroller.stopTimer();
        active = false;
    }

    int currentStatus()
    {
        /*
            focus + active : 0
            focus + inactive : 1
            break + active : 2
            break + inactive : 3
            idle + active : 4
            idle + inactive : 5
        */
        int fac_status, faa_status;
        switch (facontroller.assistMode)
        {
        case FocusAssistMode::fa_focus:
            fac_status = 0;
            break;
        case FocusAssistMode::fa_break:
            fac_status = 1;
            break;
        case FocusAssistMode::fa_idle:
            fac_status = 2;
            break;
        default:
            break;
        }
        switch (active)
        {
        case true:
            active = 0;
            break;
        case false:
            active = 1;
            break;
        default:
            break;
        }
        return fac_status + faa_status;
    }

    // Function Button functions
    void onSinglePushFB(void) override {}
    void onHoldPushFB(void) override {}
    void onDoublePushFB(void) override {}

    uint16_t focusRemainTime() { facontroller.focusTimeSec - facontroller.getTimerCount(); }
    uint16_t breakRemainTime() { facontroller.breakTimeSec - facontroller.getTimerCount(); }

    void drawFocusRemainTime()
    {
        uint16_t remainsecs = focusRemainTime();
        oledcontroller.printInCenter(String(String((int)remainsecs / 3600) + ((int)remainsecs / 60)),
                                     2, 1, 0, -10); // hour : minute
    }

    void drawBreakRemainTime()
    {
        uint16_t remainsecs = breakRemainTime();
        oledcontroller.printInCenter(String(String((int)remainsecs / 3600) + ((int)remainsecs / 60)),
                                     1, 1, 0, -10); // hour : minute
    }

    void drawTime()
    {
        if (facontroller.assistMode == FocusAssistMode::fa_idle)
        {
            oledcontroller.printInCenter("HOLD,Go!",
                                         1, 1, 0, -10);
        }
        if (facontroller.assistMode == FocusAssistMode::fa_focus)
        {
            drawFocusRemainTime();
        }
        else if (facontroller.assistMode == FocusAssistMode::fa_break)
        {
            drawBreakRemainTime();
        }
    }

    // both return past time per 48 units (instead of percent).
    uint16_t focusPastPer48() { return floor((facontroller.getTimerCount()) * 48 / facontroller.focusTimeSec); }
    uint16_t breakPastPer48() { return floor((facontroller.getTimerCount()) * 48 / facontroller.breakTimeSec); }

    void drawBackground()
    {
        oledcontroller.fillBlueArea();
        // draw and remove squares.
        if (facontroller.assistMode == FocusAssistMode::fa_idle)
        {
            return;
        }
        if (facontroller.assistMode == FocusAssistMode::fa_focus)
        {
            display.drawRect(0, 16, 128, focusPastPer48(), 0);
        }
        else if (facontroller.assistMode == FocusAssistMode::fa_break)
        {
            display.drawRect(0, 16, 128, breakPastPer48(), 0);
        }
    }

    void drawTitle()
    {
        if (facontroller.assistMode == FocusAssistMode::fa_idle)
        {
            oledcontroller.printInCenter("Focus Assist",
                                         1, 1, 0, 10);
        }
        if (facontroller.assistMode == FocusAssistMode::fa_focus)
        {
            oledcontroller.printInCenter("Focus",
                                         1, 1, 0, 10);
        }
        else if (facontroller.assistMode == FocusAssistMode::fa_break)
        {
            oledcontroller.printInCenter("Break",
                                         1, 1, 0, 10);
        }
    }

    void updateScreen()
    {
        drawBackground();
        drawTime();
        drawTitle();
    }

    static void FocusAssistActivity::static_updateScreen(void *pvParameter)
    {
        FocusAssistActivity *faa = static_cast<FocusAssistActivity *>(pvParameter); //obtain the instance pointer
        faa->updateScreen();                                                        //dispatch to the member function, now that we have an instance pointer
    }
};