#include <Arduino.h>

enum ActivityStatus
{
    create,
    appear,
    running,
    pause,
    resume,
    destroy,
};

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
        case create:
            onCreate();
            break;
        case appear:
            onAppear();
            break;
        case running:
            break;
        case pause:
            onPause();
            break;
        case resume:
            onResume();
            break;
        case destroy:
            onDestroy();
            break;
        default:
            break;
        }
    }
    bool isSpecialActivity()
    {
        return _specialActivity;
    }

    Activity()
    {
        changeStatusTo(create);
    }
    ~Activity()
    {
        changeStatusTo(destroy);
    }

    // Activity cycle functions
    /*
     Set defaults or load data from memory.
    */
    void onCreate() {}
    /*
     Set and make ready to display the activity.
    */
    void onAppear() {}
    /*
     Save latest status of activity and make ready to leave the screen.
    */
    void onPause() {}
    /*
     Reappear activity with latest status from memory.
    */
    void onResume() {}
    /*
     Save status to flash if needed and make ready to destroy from memory.
    */
    void onDestroy() {}

    // Function Button functions
    void onSinglePushFB(void) {}
    void onHoldPushFB(void) {}
    void onDoublePushFB(void) {}

    // This function will run if app needs to continue it's process.
    void backgroundRun(void) {}
};