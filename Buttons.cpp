/**
This library lets you use multiple buttons.
To use this library first you need to define how many buttons that you will use.
After that you need to define a button then add it to the pool using add function.
When these steps are done you will need to update this library to be able to use button functions.
The pin that the button is connected to should be active low.
See the example codes in the examples folder.

This library was written by Anıl Gençer. 
If you have anything to ask about this library my e-mail address is anlgncr1@gmail.com
 
*/

#include "Arduino.h"
#include "Buttons.h"

/*
	Constructor takes one parameter.
	length => The number of buttons that you wish to use.
*/
Buttons::Buttons(uint8_t length){
	buttons_length = length;
	buttons = (Button**)calloc(length, sizeof(Button*));
}

/*
	This method sets the button toggle time.
	Button will change its status after this time.
	Time => The time that button needs to change its status
*/
void Buttons::setDebounceTime(unsigned long time){
	debounce_time = time;
}

/*
	This method adds the button you have defined to the pool
	This method does not add the button if you try to add it twice or 
	if you try to add more than the length of buttons you have defined.
	_button => The address of the button you wish to add to the pool.
	Returns true if adding to the pool is succesfull
*/
bool Buttons::add(Button* _button, uint8_t pin){
	if(buttons_index >= buttons_length)
		return false;
	
	for(uint8_t i=0; i<buttons_index; i++)
		if(buttons[i] == _button)
			return false;
	
	pinMode(pin, INPUT);
	_button->pin = pin;
	
	if(_button->longPressedTime == 0)
		_button->longPressedTime = 500;
	
	_button->preLongPressed = true;
	_button->up = true;
	buttons[buttons_index] = _button;
	buttons_index++;
	
	return true;
}

/*
	This method creates a new button with given pin.
	pin => The pin connected to the button.
	Returns the address of the button object if succeeds
	Return NULL if fails
*/
Buttons::Button* Buttons::create(uint8_t pin){
	if(buttons_index >= buttons_length)
		return NULL;
	
	Button* _button = (Button*)malloc(sizeof(Button));
	
	byte *tempAddr = (byte*)_button; 
	for(byte i=0; i<sizeof(Button); i++){
		tempAddr[i] = 0;
	}
	
	if(_button){
		pinMode(pin, INPUT);
		_button->pin = pin;
		_button->longPressedTime = 500;
		_button->preLongPressed = true;
		_button->up = true;
		buttons[buttons_index] = _button;
		buttons_index++;
		return _button;
	}
	return NULL;
}

/*
	This method removes the button from the pool
	_button => The address of the button you wish to remove from the pool.
	Returns false if fails.
*/
bool Buttons::remove(Button* _button)
{	
	for(uint8_t i=0; i<buttons_index; i++){
		if(buttons[i] == _button){
			buttons[i] = NULL;
			dispose();
			return true;
		}
	}
	return false;
}

/*
	This method is private. It organizes the pool.
*/
void Buttons::dispose(){
	uint8_t real_index = 0;

	for(uint8_t i=0; i<buttons_length; i++){
		if(buttons[i] != NULL){
			if(real_index != i){
				buttons[real_index] = buttons[i];
				buttons[i] = NULL;
			}
			real_index++;
		}
	}
	buttons_index = real_index;
}

/*
	This method returns true if the spesific button is down.
	It returns true for once for a push
	_button => The address of the button that you want to detect if it is down
*/
bool Buttons::buttonDown(Button* _button){
	if(_button->pushed){
		_button->pushed = false;
		return true;
	}
	return false;
}

bool Buttons::buttonLongDown(Button* _button){
	if(_button->longPressed){
		_button->longPressed = false;
		return true;
	}
	return false;
}

/*
	This method returns true if the specific button is up.
	It returns true for once for a release.
	_button => The address of the button that you want to detect if it is up
*/
bool Buttons::buttonUp(Button* _button){
	if(_button->released){
		_button->released = false;
		return true;
	}
	return false;
}

void Buttons::statusChanged(Button* _button){
	if(_button->onChanged != NULL)
		(*(_button->onChanged))(_button);
}

/*
	The method returns the index of the last button that added
*/
uint8_t Buttons::getIndex(){
	return buttons_index;
}

/*
	This method updates the status of the buttons
*/
void Buttons::update()
{
	for(uint8_t i=0; i<buttons_index; i++)
	{
		Button* _button = buttons[i];
			
		if(digitalRead(_button->pin))
		{
			_button->down_lastTime = millis();
			if(_button->up && (millis() - _button->up_lastTime) > debounce_time){
				_button->up = false;
				_button->down = true;
				_button->pushed = true;
				
				statusChanged(_button);
				
				if(_button->onButtonDown != NULL)
					(*(_button->onButtonDown))(_button);
			}
		}	
		else
		{
			_button->up_lastTime = millis();
			if(_button->down && (millis() - _button->down_lastTime) > debounce_time){
				_button->up = true;
				_button->down = false;
				_button->released = true;
				_button->preLongPressed = true;
			
				statusChanged(_button);
				
				if(_button->onButtonUp != NULL)
					(*(_button->onButtonUp))(_button);
			}
		}
		
		if(_button->preLongPressed && (millis() - _button->up_lastTime > _button->longPressedTime)){
			_button->preLongPressed = false;
			_button->longPressed = true;
			
			if(_button->onLongPressed != NULL)
				(*(_button->onLongPressed))(_button);
			
			statusChanged(_button);
		}
	}
}




