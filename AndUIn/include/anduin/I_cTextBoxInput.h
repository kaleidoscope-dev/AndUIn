#pragma once
#include "anduin.h"
#include "I_cTextBox.h"



// TODO:
// 
// * Ako je font size >

class I_cTextBoxInput : public I_cTextBox
{
 public:
	 I_cTextBoxInput();
	~I_cTextBoxInput();

	
	

private:
	void HandleEvent(SDL_Event *event);


};