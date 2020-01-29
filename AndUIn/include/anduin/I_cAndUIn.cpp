#include "I_cAndUIn.h"
#include <string>


I_cAndUIn *gAnduin = NULL;




I_cAndUIn::I_cAndUIn()
{
}


I_cAndUIn::~I_cAndUIn()
{
 for (size_t c=0;c<vObjectList.size();c++)
     {
      I_cObject *ptr_object = vObjectList[c];
	  delete ptr_object;
	 }


}


void I_cAndUIn::DeleteWindow(I_cObject *object)
{
 for (size_t c=0;c<vObjectList.size();c++)
     {
      I_cObject *ptr_object = vObjectList[c];
	  if (object == ptr_object)
	     {
	      vObjectList.erase(vObjectList.begin()+c);
		  delete object;
		  object = NULL;
		 }
		  
	 }
 
}



// TODO: Nije CreateAnduinWindow nego Ubaci u anduinHandle event loop tako da se anduin procesira evente iz prozora
void I_cAndUIn::CreateAnduinWindow(I_cObject *wnd)
{
 //vWindowList.push_back(wnd);
 vObjectList.push_back(wnd);
 vObjectListZ.push_back(wnd);
}



void I_cAndUIn::AddWidget(I_cWindow *parent_wnd, I_cWidget *wdg)
{
	parent_wnd->vWidgetList.push_back(wdg);
}



void I_cAndUIn::HandleEvent(ANDUIN_EVENT_TYPE type)
{

	I_cWindow *wnd_active = GetActiveWindow();
	if (!wnd_active)
		return;

	wnd_active->HandleEvent(type);
	return;


}



void I_cAndUIn::Draw(void)
{

 	for (size_t c=0;c<vObjectList.size();c++)
	{
	 I_cObject *wnd = vObjectList[c];
	 if (wnd->GetVisible())
		 wnd->Draw();
	}


 //I_cWindow *wnd = GetActiveWindow();
 //if (wnd)
	//GAMEAPI::RenderTextClr(500,50,AndUIn::Red,"Active wnd: %s",wnd->GetName().c_str());
	//else GAMEAPI::RenderTextClr(500,50,AndUIn::Red,"Active wnd: NULL");
}


void I_cAndUIn::DrawZ(void)
{

 	for (size_t c=0;c<vObjectListZ.size();c++)
	{
	 I_cObject *wnd = vObjectList[c];
	 if (wnd->GetVisible())
		 wnd->Draw();
	}
}



void I_cAndUIn::ToTop(I_cObject *object)
{
 for (size_t c=0;c<vObjectList.size();c++)
     {
      I_cObject *ptr_object = vObjectList[c];
	  if (object == ptr_object)
	     {
	      vObjectList.erase(vObjectList.begin()+c);
		 }
	 } 
 vObjectList.push_back(object);
}


I_cObject *I_cAndUIn::GetActiveObject(void)
{
	for (size_t c=0;c<vObjectList.size();c++)
	{
		I_cObject *wnd = vObjectList[c];
		if (wnd->GetFocus() == true)
			return wnd;
	}

	return 0;
}



I_cWindow *I_cAndUIn::GetActiveWindow(void)
{
	for (size_t c=0;c<vObjectList.size();c++)
	{
		I_cWindow *wnd = (I_cWindow*)vObjectList[c];
		if (wnd->GetFocus() == true)
			return wnd;
	}

	return 0;
}




void I_cAndUIn::SetActiveWindow(I_cWindow *window)
{
 I_cWindow *wnd_active = GetActiveWindow();
 if (wnd_active)   
    {
     wnd_active->SetActive(false);
	}

 
 ToTop(window);
 window->SetActive(true);
 window->Show();
}


void I_cAndUIn::SetActiveWindow(I_cObject *object)
{
	I_cObject *obj_active = GetActiveObject();
	if (obj_active)   
	{
		obj_active->SetActive(false);
	}

	ToTop(object);
	object->SetActive(true);
	object->SetVisible(true);
}

