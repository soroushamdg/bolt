#include <Arduino.h>
#include <Apps/BoltBoard/Activities/activity.h>
#include <map>

class ActivityManager
{
private:
    std::map<String, Activity> activities;
    String activityQueue;
    uint8_t activityAppearanceTimeCounter; //?

public:
    ActivityManager()
    {
    }

    int insertActivity(Activity activity) {}

    String nextActivityID(void) {}
    String currentActivityID(void) {}
    String gotoNextActivity(void) {}
    String restartActivity(String id) {}
    String destroyActivity(String id) {}

    String urgentGotoActivity(String id) {} //?
};