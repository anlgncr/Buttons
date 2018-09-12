#include <Buttons.h>

Buttons my_buttons(1);
Buttons::Button* my_button1;

void setup() {
  Serial.begin(9600);
  my_button1 = my_buttons.create(5);
  my_button1->onButtonDown = onPushed;
}

void loop() {
  my_buttons.update();
}

void onPushed(Buttons::Button* _buton){
  Serial.println("Button1 is pushed");
}