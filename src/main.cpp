#include <Arduino.h>
#include <Keyboard.h>

void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  delay(2000);
  Serial.print("Switch to Notepad!");
  delay(3000);

  Keyboard.print("Testing XIAO HID keyboard...1...2...3");
}

void loop() {

}
