#include <Arduino.h>

class Activity
{
private:
    ActivityStatus current_status;
    bool _specialActivity = false;

public:
    String id;
    int queueIndex;
    void changeStatusTo(ActivityStatus status)
    {
        current_status = status;
        switch (status)
        {
        case ActivityStatus::created:
            onCreate();
            break;
        case ActivityStatus::appear:
            onAppear();
            break;
        case ActivityStatus::running:
            break;
        case ActivityStatus::pause:
            onPause();
            break;
        case ActivityStatus::resume:
            onResume();
            break;
        case ActivityStatus::destroy:
            onDestroy();
            break;
        default:
            break;
        }
    }

    void setSpecialActivity()
    {
        _specialActivity = true;
    }

    bool isSpecialActivity()
    {
        return _specialActivity;
    }

    Activity()
    {
        
    }
    ~Activity()
    {
    }

    // Activity cycle functions
    /*
     Set defaults or load data from memory.
    */
    virtual void onCreate() {}
    /* 
     Set and make ready to display the activity.
    */
    virtual void onAppear() {}
    /*
     Save latest status of activity and make ready to leave the screen.
    */
    virtual void onPause() {}
    /*
     Reappear activity with latest status from memory.
    */
    virtual void onResume() {}
    /*
     Save status to flash if needed and make ready to destroy from memory.
    */
    virtual void onDestroy() {}

    // Function Button functions
    virtual void onSinglePushFB(void) {}
    virtual void onHoldPushFB(void) {}
    virtual void onDoublePushFB(void) {}

    // This function will run if app needs to continue it's process.
    virtual void backgroundRun(void) {}
};