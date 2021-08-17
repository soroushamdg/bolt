#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>

#include <DisplayController/display_controller.h>
DisplayController oledcontroller;

#include <DisplayController/animator/animator.h>
Animator animator = Animator();

#include <DisplayController/animations/splash_bolt.h>
#include <DisplayController/animations/loading_infinity.h>

#include <DisplayController/StatusBarDrawer/statusbar_drawer.h>
StatusBarDrawer stbardrawer = StatusBarDrawer();

#include <DisplayController/ClockInterfaceController/clock_face_mini_status.h>
ClockfaceMiniStatusbar cmstatus = ClockfaceMiniStatusbar();

#include <DisplayController/ClockInterfaceController/clock_face_analog.h>
ClockfaceAnalogController cacontroller = ClockfaceAnalogController();

#include <DisplayController/ClockInterfaceController/clock_face_digital.h>
ClockfaceDigitalController cdcontroller = ClockfaceDigitalController();

#include <TimeController/time_controller.h>
TimeController timecontroller = TimeController();

void setup()
{
  Serial.begin(9600);
  Wire.begin(21, 22);
  Wire.setClock(3400000);

  oledcontroller.init();

  animator.animateArray(34, 17, 0, 1, splash_bolt, 0, 16, 128, 48);

  stbardrawer.DrawBluetoothIcon();
  stbardrawer.DrawFocusIcon();
  stbardrawer.DrawAlarmIcon();

  // animator.animateArray(169, 83, 0, 0, loading_infinity, 40, 16, 48, 48);

  // oledcontroller.writehello();
  // cmstatus.drawMiniStatus(11, 40, "20 Aug, 2021");

  // cacontroller.drawAnalogFace(10, 10);

  // delay(500);

  cdcontroller.drawDigitalFace(2, 2, 3, 1);

  cmstatus.drawMiniStatus(2, 3, "22 Aug, 2021");
}

void loop()
{
  // put your main code here, to run repeatedly:
}