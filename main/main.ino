#include <BleKeyboard.h>

BleKeyboard bleKeyboard("PageTurner", "Benjamin", 100);

const int BTN_NEXT = 21;
const int BTN_PREV = 22;
const int STATUS_LIGHT = 2;
const int HOLD_PIN = 4;

const int KEEPALIVE = 3000;
unsigned long lastActivity = 0;

void setup() {
  Serial.begin(115200);
  pinMode(HOLD_PIN, OUTPUT);
  digitalWrite(HOLD_PIN, HIGH);
  Serial.println("Hold pin HIGH");

  pinMode(BTN_NEXT, INPUT_PULLDOWN);
  pinMode(BTN_PREV, INPUT_PULLDOWN);
  Serial.println("Buttons initialized to INPUT");
  bleKeyboard.begin();
  Serial.println("Keyboard started");
  pinMode(STATUS_LIGHT, OUTPUT);
  digitalWrite(STATUS_LIGHT, HIGH);
  Serial.println("Status: ON"); 
}

void loop() {
  if (!bleKeyboard.isConnected()) 
  {
    Serial.println("Not connected!! Delay and return...");
    digitalWrite(STATUS_LIGHT, LOW);
    delay(100);
    digitalWrite(STATUS_LIGHT, HIGH);
    delay(100);
    digitalWrite(STATUS_LIGHT, LOW);
    delay(100);
    digitalWrite(STATUS_LIGHT, HIGH);
    delay(2000);
    return;
  }
  else
  {
    bool pressed = false;
    
    if (digitalRead(BTN_NEXT) == HIGH) {
      Serial.println("BUTTON NEXT PRESSED, SENDING KEYSTROKE");
      bleKeyboard.write(KEY_RIGHT_ARROW);
      digitalWrite(STATUS_LIGHT, LOW);
      pressed = true;
      delay(200);
      digitalWrite(STATUS_LIGHT, HIGH);
    }
    else if (digitalRead(BTN_PREV) == HIGH) {
      Serial.println("BUTTON PREV PRESSED, SENDING KEYSTROKE");
      bleKeyboard.write(KEY_LEFT_ARROW);
      digitalWrite(STATUS_LIGHT, LOW);
      pressed = true;
      delay(200);
      digitalWrite(STATUS_LIGHT, HIGH);
    }

    else {
      Serial.println("No buttons detected...");
    }

    if (pressed)
    {
      lastActivity = millis();
    }

    if (millis() - lastActivity > KEEPALIVE) {
      bleKeyboard.releaseAll();
      lastActivity = millis();
      Serial.println("Keepalive sent");
    }
  }
  delay(100);

}