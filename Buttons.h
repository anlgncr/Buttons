#ifndef Button_h
#define Button_h
#include "Arduino.h"

class Buttons
{
  public:
  
  /*
	The button structure has 10 variables. It occupies (1,1,1,1,1,1,4,4,2,2) 18 bytes in the memory.
	And for every pointer of button it takes 2 bytes
	The pointer of the pointer of buttons take 2 bytes
	if we calculate the total amount of these the formula is 18*button_number + 8
	pin => The pin connected to the button
	status => The status of the button. It is true if button is pushed.
	up => This is true if button is up
	down => This is true if the button is down
	pushed => This is true when the button is pushed down
	released => This is true when the button is released up
	up_lastTime => The last time that the button is up
	down_lastTime => The last time that the button is down
	onButtonUp => This method will be called when the button is up
	onButtonDown => This method will be called when the button is down
  */
	struct Button{
		uint8_t pin;
		bool status;
		bool up;
		bool down;
		bool pushed;
		bool released;
		bool longPressed;
		bool preLongPressed;
		unsigned long up_lastTime;
		unsigned long down_lastTime;
		unsigned long longPressedTime;
		void (*onButtonUp)(Button*);
		void (*onButtonDown)(Button*);
		void (*onChanged)(Button*);
		void (*onLongPressed)(Button*);
		void* object;
	};
  
	// Constructor
	Buttons(uint8_t);
	
	//Returns the last index of the buttons in the pool
	uint8_t getIndex();
	
	// Updates the buttons status
	void update();
	
	// Sets the bounce time
	void setDebounceTime(unsigned long);
	
	// Adds the button to the pool
	bool add(Button*, uint8_t);
	
	// Removes the button from the pool
	bool remove(Button*);
	
	// Return true when the button is up
	bool buttonUp(Button*);
	
	// Return true when the button is down
	bool buttonDown(Button*);
	
	bool buttonLongDown(Button*);
	
	// Creates a new button object and returns its address
	Button* create(uint8_t);
	
  private:
  
	// The array of addresses of the buttons (The pool)
	Button** buttons;
	
	// Last index of the the buttons
    uint8_t buttons_index = 0;
	
	// The max size of the buttons in the pool
	uint8_t buttons_length = 0;
	
	// The time that buttons need to change its status
	unsigned long debounce_time = 40;
	
	// Reorders the pool
	void dispose();
	
	void statusChanged(Button*);
};

#endif