#include <Buttons.h>

#define LEFT_ARROW    5
#define UP_ARROW      6
#define RIGHT_ARROW   7
#define DOWN_ARROW    8

Buttons buttonManager(4);
Buttons::Button upArrow, downArrow, rightArrow, leftArrow;

void buttonListener(Buttons::Button* my_button)
{ 
  if(buttonManager.buttonUp(my_button)){
    switch(my_button->pin){
      case LEFT_ARROW   :  Serial.println("Arrow left released");  break;
      case UP_ARROW     :  Serial.println("Arrow up released");    break;
      case RIGHT_ARROW  :  Serial.println("Arrow right released"); break;
      case DOWN_ARROW   :  Serial.println("Arrow down released");  break;
    }
  }
  else if(buttonManager.buttonDown(my_button)){
    switch(my_button->pin){
      case LEFT_ARROW   :  Serial.println("Arrow left pushed");  break;
      case UP_ARROW     :  Serial.println("Arrow up pushed");    break;
      case RIGHT_ARROW  :  Serial.println("Arrow right pushed"); break;
      case DOWN_ARROW   :  Serial.println("Arrow down pushed");  break;
    }
  }
  else if(buttonManager.buttonLongDown(my_button)){
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

  buttonManager.add(&leftArrow, LEFT_ARROW);
  leftArrow.onChanged = buttonListener;

  buttonManager.add(&upArrow, UP_ARROW);
  upArrow.onChanged = buttonListener;
 
  buttonManager.add(&rightArrow, RIGHT_ARROW);
  rightArrow.onChanged = buttonListener;

  buttonManager.add(&downArrow, DOWN_ARROW);
  downArrow.onChanged = buttonListener;
}

void loop() {
  buttonManager.update();
}
