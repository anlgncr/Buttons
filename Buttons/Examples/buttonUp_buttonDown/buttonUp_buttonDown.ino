#include <Buttons.h>

Buttons my_buttons(2);
Buttons::Button my_button1, my_button2;

void setup() {
  Serial.begin(9600);
  
  my_button1.pin = 5;
  my_buttons.add(&my_button1);

  my_button2.pin = 6;
  my_buttons.add(&my_button2);
}

void loop() {
  my_buttons.update();
  
  if(my_buttons.buttonDown(&my_button1)){
    Serial.println("Button1 Pushed");
  }
  
  if(my_buttons.buttonUp(&my_button1)){
    Serial.println("Button1 Released");
  }

  if(my_buttons.buttonDown(&my_button2)){
    Serial.println("Button2 Pushed");
  }
  
  if(my_buttons.buttonUp(&my_button2)){
    Serial.println("Button2 Released");
  } 
}
