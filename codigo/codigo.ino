#include <Joystick.h>

#define NUMBER_BUTTONS 4
#define DEBOUNCE_TIME 15

int pins[NUMBER_BUTTONS] = {6, 7, 8, 9};
bool last_state[NUMBER_BUTTONS] = {0, 0, 0, 0};
unsigned long last_debounce[NUMBER_BUTTONS] = {0, 0, 0, 0};

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, // Device ID and type
  NUMBER_BUTTONS, 0,  // Button Count, Hat Switch Count
  false, false, false,   // No X, Y, or Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {

  for(int i=0; i<NUMBER_BUTTONS; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  } 
  Joystick.begin();
}

void loop() {
  for(int i=0; i<NUMBER_BUTTONS; i++)
  {
    bool reading = !digitalRead(pins[i]);
    bool time_debounced = abs(millis() - last_debounce[i]) > DEBOUNCE_TIME;
    if (last_state != reading && time_debounced){
      last_debounce[i] = millis();
      last_state[i] = reading;
      Joystick.setButton(i, reading);
    }
  }
}
