#include <Arduino.h>

// 'icons8-focal-length-50', 15x15px
const uint8_t status_icon_focus[] = {
    0x00, 0x04, 0x00, 0x1c, 0x00, 0x70, 0x01, 0xd8, 0x07, 0x98, 0x1f, 0x88, 0x73, 0x8c, 0xc3, 0x8c,
    0x73, 0x8c, 0x1f, 0x8c, 0x07, 0x98, 0x01, 0xd8, 0x00, 0x70, 0x00, 0x1c, 0x00, 0x00};
// 'icons8-bluetooth-50', 15x15px
const uint8_t status_icon_bluetooth[] = {
    0x00, 0x00, 0x01, 0x00, 0x01, 0x80, 0x01, 0xc0, 0x0d, 0x60, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80,
    0x07, 0xc0, 0x0f, 0xe0, 0x0d, 0x60, 0x01, 0xc0, 0x01, 0x80, 0x01, 0x00, 0x00, 0x00};
// 'icons8-alarm-24(1)', 15x15px
const uint8_t status_icon_alarm[] = {
    0x00, 0x00, 0x13, 0x90, 0x33, 0x98, 0x7f, 0xfc, 0x7f, 0xfc, 0x6f, 0xec, 0x0f, 0xe0, 0x0f, 0xe0,
    0x0f, 0xe0, 0x0f, 0xe0, 0x1f, 0xf0, 0x1f, 0xf0, 0x01, 0x00, 0x03, 0x80, 0x00, 0x00};