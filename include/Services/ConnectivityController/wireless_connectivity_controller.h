#include <Arduino.h>
#include "WiFi.h"
#include <HTTPClient.h>

class WirelessConnectivityController
{
private:
    char *_ssid;
    char *_password;
    bool active = false;
    bool hasssidpass = false;

    String httpGETRequest(String server)
    {
        WiFiClient client;
        HTTPClient http;

        // Your Domain name with URL path or IP address with path
        http.begin(client, server);

        // Send HTTP POST request
        int httpResponseCode = http.GET();

        String payload = "{}";

        if (httpResponseCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            payload = http.getString();
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();

        return payload;
    }

public:
    WirelessConnectivityController()
    {
    }

    bool init()
    {
        if (!hasssidpass)
        {
            return false;
        }
        Serial.println("WiFi Starting...");
        WiFi.begin(_ssid, _password);
        int attempts = 0;
        delay(3000);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi..");
            attempts++;
            if (attempts == 6)
            {
                Serial.println("WiFi Failed to connect");
                return false;
            }
        }

        if (WiFi.isConnected())
        {
            Serial.println("WiFi Connected.");
        }
        return true;
    }

    void setSSIDPassword(char *ssid, char *password)
    {
        _ssid = ssid;
        _password = password;
        hasssidpass = true;
    }

    bool isConnected()
    {
        return WiFi.isConnected();
    }

    String sendGETRequest(String server)
    {
        return httpGETRequest(server);
    }
};