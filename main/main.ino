#include <BleKeyboard.h>

BleKeyboard bleKeyboard("PageTurner", "YourName", 100);

const int BTN_NEXT = 12;
const int BTN_PREV = 14;

void setup() {
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_PREV, INPUT_PULLUP);
  bleKeyboard.begin();
}

void loop() {
  if (!bleKeyboard.isConnected()) return;

  if (digitalRead(BTN_NEXT) == LOW) {
    bleKeyboard.write(KEY_RIGHT_ARROW); // or PAGE_DOWN
    delay(200); // debounce
  }

  if (digitalRead(BTN_PREV) == LOW) {
    bleKeyboard.write(KEY_LEFT_ARROW);
    delay(200);
  }
}