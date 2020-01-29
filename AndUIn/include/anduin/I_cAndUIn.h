#pragma once
#include "anduin.h"
#include "I_cWidget.h"
#include "I_cTextBox.h"
#include "I_cButton.h"
#include "I_cLabel.h"
#include "I_cTextBoxInput.h"
#include "I_cWindow.h"
#include "I_cCheckButton.h"
#include "I_cImageButton.h"
#include "I_cObject.h"
#include "FastDelegate/FastDelegate.h"

using namespace AndUIn;



class I_cAndUIn
{
 public:
	 I_cAndUIn();
	 ~I_cAndUIn();

	
	//void init(void);
	 I_cWindow *CreateAnduinWindow(std::string name = "AndUIn Window");
	 void CreateAnduinWindow(I_cObject *wnd);

	 void AddWidget(I_cWindow *parent_wnd, I_cWidget *wdg);

	 void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);

	 void Draw(void);
	 void DrawZ(void);
	 void ToTop(I_cObject *object);
	 I_cWindow *GetActiveWindow(void);
	 I_cObject *GetActiveObject(void);
	 void SetActiveWindow(I_cWindow *window);
	 void SetActiveWindow(I_cObject *object);
	 void DeleteWindow(I_cObject *object);

 private:
	 std::vector<I_cObject*>vObjectList;
	 std::vector<I_cObject*>vObjectListZ;



};


extern I_cAndUIn *gAnduin;



