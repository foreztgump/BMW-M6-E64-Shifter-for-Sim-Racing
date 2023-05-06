#include <Joystick.h>
#include <Bounce2.h>

Joystick_ Joystick;
const int pinToButtonMap = 1;
Bounce debouncer[4] = {Bounce(), Bounce(), Bounce(), Bounce()};
int lastButtonState[4] = {0, 0, 0, 0};

void setup() {
  Joystick.begin();

  for (int i = 0; i < 4; i++) {
    debouncer[i].attach(i + pinToButtonMap, INPUT_PULLUP);
    debouncer[i].interval(5);
  }
}

void loop() {
  // Read the state of each button and update the debouncer
  for (int i = 0; i < 4; i++) {
    debouncer[i].update();
    int buttonState = debouncer[i].read();

    // Determine if the button state has changed
    if (buttonState != lastButtonState[i]) {
      // Save the new button state
      lastButtonState[i] = buttonState;

      // Map button states to joystick buttons
      if (lastButtonState[0] == 0 && lastButtonState[1] == 1 && lastButtonState[2] == 1 && lastButtonState[3] == 0) {
        // reset all joystick buttons to 0 if button state is 0110
        Joystick.setButton(0, 0);
        Joystick.setButton(1, 0);
        Joystick.setButton(2, 0);
        Joystick.setButton(3, 0);
      }
      else if (lastButtonState[0] == 0 && lastButtonState[1] == 1 && lastButtonState[2] == 1 && lastButtonState[3] == 1) {
        Joystick.setButton(0, 1);
      }
      else if (lastButtonState[0] == 1 && lastButtonState[1] == 1 && lastButtonState[2] == 1 && lastButtonState[3] == 0) {
        Joystick.setButton(3, 1);
      }
      else if (lastButtonState[0] == 1 && lastButtonState[1] == 1 && lastButtonState[2] == 0 && lastButtonState[3] == 1) {
        Joystick.setButton(0, 0);
        Joystick.setButton(1, 0);
        Joystick.setButton(2, 0);
        Joystick.setButton(3, 0);
      }
      else if (lastButtonState[0] == 1 && lastButtonState[1] == 0 && lastButtonState[2] == 1 && lastButtonState[3] == 1) {
        Joystick.setButton(2, 1);
        Joystick.setButton(1, 0);
        Joystick.setButton(0, 0);
        Joystick.setButton(3, 0);
      }
    }
  }
}
