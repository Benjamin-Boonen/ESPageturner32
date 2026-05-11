#include <BleKeyboard.h>

BleKeyboard bleKeyboard("PageTurner", "Benjamin", 100);

const int BTN_NEXT = 37;
const int BTN_PREV = 39;
const int STATUS_LIGHT = 19;
const int HOLD_PIN = 4;

void setup() {
  pinMode(HOLD_PIN, OUTPUT);
  digitalWrite(HOLD_PIN, HIGH);

  pinMode(BTN_NEXT, INPUT);
  pinMode(BTN_PREV, INPUT);
  bleKeyboard.begin();
  pinMode(STATUS_LIGHT, OUTPUT);
  digitalWrite(STATUS_LIGHT, HIGH);
}

void loop() {
  if (!bleKeyboard.isConnected()) 
  {
    delay(500);
    return;
  }
  
  if (digitalRead(BTN_NEXT) == LOW) {
    bleKeyboard.write(KEY_RIGHT_ARROW);
    delay(200);
  }

  if (digitalRead(BTN_PREV) == LOW) {
    bleKeyboard.write(KEY_LEFT_ARROW);
    delay(200);
  }

  delay(10);

}