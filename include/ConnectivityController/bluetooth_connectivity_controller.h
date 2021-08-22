#include <Arduino.h>
#include "BluetoothSerial.h"

// /* Check if Bluetooth configurations are enabled in the SDK */
// /* If not, then you have to recompile the SDK */
// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// #endif

BluetoothSerial BTSerial;

class BluetoothConnectivityController
{
public:
    bool active = false;
    String readBuff;

    BluetoothConnectivityController()
    {
    }

    void init()
    {
        Serial.println("Bluetooth Starting...");
        BTSerial.begin("⚡Bolt");
        active = true;
        Serial.println("Bluetooth Started -> Ready to pair...");
    }

    bool hasClient()
    {
        return BTSerial.hasClient();
    }

    void sendData(String data)
    {
        BTSerial.println(data);
    }

    bool readData()
    {
        String tempBuff = BTSerial.readString();
        if (!tempBuff.isEmpty())
        {
            readBuff = tempBuff;
            return true;
        }
        return false;
    }
};