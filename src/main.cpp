#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>

#include <Services/enums/ActivityStatusEnum.h>

#include <Services/DisplayController/display_controller.h>
DisplayController oledcontroller = DisplayController();

#include <Services/DisplayController/animator/animator.h>
Animator animator = Animator();

#include <Services/DisplayController/animations/splash_bolt.h>
#include <Services/DisplayController/animations/loading_infinity.h>

#include <Services/DisplayController/StatusBarDrawer/statusbar_drawer.h>
StatusBarDrawer stbardrawer = StatusBarDrawer();

#include <Apps/BoltWatch/watchfaces/clock_face_mini_status.h>
ClockfaceMiniStatusbar cmstatus = ClockfaceMiniStatusbar();

#include <Services/ConnectivityController/wireless_connectivity_controller.h>
WirelessConnectivityController wificc = WirelessConnectivityController();

#include <Services/LEDController/led_controller.h>
LEDController redonboardled = LEDController(2, LOW);

#include <Apps/FocusAssist/focus_assist_activity.h>

void setup()
{
  Serial.begin(9600);
  Wire.begin(21, 22);
  Wire.setClock(3400000);

  oledcontroller.init();

  animator.animateArray(34, 17, 0, 1, splash_bolt, 0, 16, 128, 48);

  // wificc.setSSIDPassword("YOUR_SSID", "YOUR_PASSWORD");

  // wificc.init();

  // if (wificc.isConnected())
  // {
  //   stbardrawer.DrawWirelessIcon();
  // }
  stbardrawer.DrawAlarmIcon();

  // animator.animateArray(169, 83, 0, 0, loading_infinity, 40, 16, 48, 48);

  // oledcontroller.writehello();
  cmstatus.drawMiniStatus(11, 23, "20 Aug, 2021");

  // cacontroller.drawAnalogFace(10, 10);

  // delay(500);

  oledcontroller.printInCenter("11 : 23", 3, 1, 0, 0);
  // display.setFont();

  // oledcontroller.printInCenter("11:23", 2, 1, 0, 0);
  display.display();
  // display.println("How are you?");
  // display.println("Third line.");
  // display.display();
  // display.setFont();
  // display.setTextSize(1.5); // Normal 1:1 pixel scale
  // display.setTextColor(1);  // Draw white text
  // display.setCursor(0, 16); // Start at top-left corner
  // display.println(F("Started Wifi."));
  // display.display();
  // delay(100);
  // display.println(F("Sending Request..."));
  // display.display();
  // display.setCursor(0, 16); // Start at top-left corner
  // display.clearDisplayArea(0, 16, 128, 48);
  // display.println(wificc.sendGETRequest("http://eu.httpbin.org/ip"));
  // display.display();

  // fac.drawBoard();

  FocusAssistActivity fac = FocusAssistActivity();
}

void loop()
{

  for (int i = 0; i < 255; i += 10)
  {
    redonboardled.analog(i);
    delay(30);
  }
  for (int i = 255; i >= 0; i -= 10)
  {
    redonboardled.analog(i);

    delay(30);
  }

  // put your main code here, to run repeatedly:
}