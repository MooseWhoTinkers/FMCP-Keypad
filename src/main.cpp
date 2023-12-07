#include <Arduino.h>
#include <Keyboard.h>

const uint8_t buttonPin = 10;
const uint16_t longClickDelay = 500;

enum buttonState_e
{
  BUTTON_NOT_PRESSED,
  BUTTON_SHORT_CLICK,
  BUTTON_LONG_CLICK,
};

/* Functions definitions*/
buttonState_e readButton(uint8_t pin);

void setup() {
  Keyboard.begin();

  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() {
  buttonState_e buttonState = readButton(buttonPin);

  if (buttonState == BUTTON_SHORT_CLICK)
  {
    Keyboard.print("Your password\n");
  }
  else if (buttonState == BUTTON_LONG_CLICK)
  {
    Keyboard.print("Menu: TODO\n");
  }
}

buttonState_e readButton(uint8_t pin)
{
  const uint16_t debounceDelay = 50;
  static bool oldPinState = 0;
  static bool pinState = 0;
  static uint32_t debounceTime = 0;
  static uint32_t clickTime = 0;
  buttonState_e buttonState = BUTTON_NOT_PRESSED;
  
  bool newPinState = digitalRead(buttonPin);

  if (oldPinState != newPinState)
  {
    debounceTime = millis();
  }

  if ((millis() - debounceTime) > debounceDelay)
  {
    if (pinState != newPinState)
    {
      pinState = newPinState;
      if (pinState == true)
      {
        clickTime = millis();
      }
      else
      {
        if ((millis() - clickTime) > longClickDelay)
        {
          buttonState = BUTTON_LONG_CLICK;
        }
        else 
        {
          buttonState = BUTTON_SHORT_CLICK;
        }
      }

    }
  }

  oldPinState = newPinState;

  return buttonState;
}

