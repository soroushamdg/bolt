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
    }

    void startFocusAssist() {}
    void pauseFocusAssist() {}
    void stopFocusAssist() {}

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