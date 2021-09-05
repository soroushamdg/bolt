#include <Apps/BoltBoard/Activities/activity.h>
#include <Apps/FocusAssist/focus_assist_controller.h>

class focusAssistActivity : public Activity
{
private:
    FocusAssistController facontroller = FocusAssistController();

public:
    focusAssistActivity()
    {
        Serial.println("Start creating...");
        id = "focus_assist_activity";
        setSpecialActivity();
        changeStatusTo(ActivityStatus::created);
        Serial.println("Finished creating...");
    }

    void updateSettings() {}

    void onCreate() override
    {
        // HERE LOAD SETTINGS AND FOCUS TIME FROM MEMORY - PREFRENCES
    }
};