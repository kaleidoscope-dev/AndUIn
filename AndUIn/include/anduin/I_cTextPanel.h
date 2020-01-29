#pragma once
#include "AndUIn.h"
#include "I_cTextBox.h"


// Panel je Text box sa slikom i mogucnosti bojanja pojedinih slova



class I_cTextPanel : public I_cTextBox
{
 public:
	 I_cTextPanel();
	~I_cTextPanel();

	//void Init(void);
	
  void Draw(void);


};