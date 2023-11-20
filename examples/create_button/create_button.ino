#include <Buttons.h>

Buttons buttonManager(1);

void setup() {
  Serial.begin(9600);
  
  Buttons::Button *myButton = buttonManager.create(3);

  myButton->onButtonDown = sayHello;
  myButton->onButtonUp = sayHello;
  myButton->onLongPressed = sayHello;
}

void loop() {
  buttonManager.update();
}

void sayHello(Buttons::Button* myButton){
  Serial.println("Hello!");
}
