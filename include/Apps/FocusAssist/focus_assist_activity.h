#include <Apps/BoltBoard/Activities/activity.h>
#include <Apps/FocusAssist/focus_assist_controller.h>

class FocusAssistActivity : public Activity
{
private:
    FocusAssistController facontroller = FocusAssistController();
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

    void drawFocusBackground()
    {
        oledcontroller.fillBlueArea();
        // draw and remove squares.
    }

    void drawFocusRemainTime()
    {
        uint16_t remainsecs = facontroller.focusTimeSec - facontroller.getTimerCount();
        oledcontroller.printInCenter(String(String((int)remainsecs / 3600) + ((int)remainsecs / 60)),
                                     2, 1, 0, -10); // hour : minute
    }

    void drawBreakRemainTime()
    {
        uint16_t remainsecs = facontroller.breakTimeSec - facontroller.getTimerCount();
        oledcontroller.printInCenter(String(String((int)remainsecs / 3600) + ((int)remainsecs / 60)),
                                     1, 1, 0, 10); // hour : minute
    }

    void updateScreen()
    {
    }
};