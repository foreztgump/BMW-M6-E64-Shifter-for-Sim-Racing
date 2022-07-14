#include <Joystick.h>

Joystick_ Joystick;
const int pinToButtonMap = 1;
int lastButtonState[4] = {0,0,0,0};

void setup() {
  Joystick.begin();
  
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  for (int index = 0; index < 4; index++) {
    int currentButtonState  = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index]) {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  if (lastButtonState[0] == 1 && lastButtonState[1] == 0 && lastButtonState[2] == 0 && lastButtonState[3] == 1) {
    //Serial.println("non-shift");
    for (int i = 0; i < 4; i++) {
      Joystick.setButton(i, 0);
    }
  }
  //upshift
  if (lastButtonState[0] == 0 && lastButtonState[1] == 0 && lastButtonState[2] == 0 && lastButtonState[3] == 1) {
    Joystick.setButton(3, 1);
  }
  //downshift
  if (lastButtonState[0] == 1 && lastButtonState[1] == 0 && lastButtonState[2] == 0 && lastButtonState[3] == 0) {
    Joystick.setButton(0, 1);
  }
}
