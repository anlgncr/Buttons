#include <Buttons.h>
#define LEFT_ARROW    5
#define UP_ARROW      6
#define RIGHT_ARROW   7
#define DOWN_ARROW    8

Buttons my_buttons(4);
Buttons::Button upArrow, downArrow, rightArrow, leftArrow;

void buttontListener(Buttons::Button* my_button)
{ 
  if(my_buttons.buttonUp(my_button)){
    switch(my_button->pin){
      case LEFT_ARROW   :  Serial.println("Arrow left released");  break;
      case UP_ARROW     :  Serial.println("Arrow up released");    break;
      case RIGHT_ARROW  :  Serial.println("Arrow right released"); break;
      case DOWN_ARROW   :  Serial.println("Arrow down released");  break;
    }
  }
  else if(my_buttons.buttonDown(my_button)){
    switch(my_button->pin){
      case LEFT_ARROW   :  Serial.println("Arrow left pushed");  break;
      case UP_ARROW     :  Serial.println("Arrow up pushed");    break;
      case RIGHT_ARROW  :  Serial.println("Arrow right pushed"); break;
      case DOWN_ARROW   :  Serial.println("Arrow down pushed");  break;
    }
  }
  else if(my_buttons.buttonLongDown(my_button)){
    switch(my_button->pin){
      case LEFT_ARROW   :  Serial.println("Arrow left pushed long");   break;
      case UP_ARROW     :  Serial.println("Arrow up pushed long");     break;
      case RIGHT_ARROW  :  Serial.println("Arrow right pushed long");  break;
      case DOWN_ARROW   :  Serial.println("Arrow down pushed long");   break;
    }
  }
  else{
    Serial.println("Something is wrong :/");
  }
}

void setup() {
  Serial.begin(9600);

  leftArrow.pin = LEFT_ARROW;
  leftArrow.longPressedTime = 2000;
  my_buttons.add(&leftArrow);
  leftArrow.onChanged = buttontListener;
  
  upArrow.pin = UP_ARROW;
  my_buttons.add(&upArrow);
  upArrow.onChanged = buttontListener;
 
  rightArrow.pin = RIGHT_ARROW;
  my_buttons.add(&rightArrow);
  rightArrow.onChanged = buttontListener;

  downArrow.pin = DOWN_ARROW;
  my_buttons.add(&downArrow);
  downArrow.onChanged = buttontListener;
}

void loop() {
  my_buttons.update();
}