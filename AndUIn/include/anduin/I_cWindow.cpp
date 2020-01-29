#include "I_cWindow.h"
#include "I_cButton.h"
#include "I_cAndUIn.h"


// render target ce biti W,H
I_cWindow::I_cWindow()
{
 window_rect_ = AndUIn::GetRect(0,0,AndUIn::ANDUIN_Window_W,AndUIn::ANDUIN_Window_H);
 //window_rect_ = AndUIn::GetRect(0,0,640,480);
 Init("Anduin Window");
 modal_ = false;
}



I_cWindow::I_cWindow(std::string name, int x, int y, int w, int h)
{
 modal_ = false;
 window_rect_ = AndUIn::GetRect(x,y,w,h);
 Init(name);
}




void I_cWindow::Init(std::string name)
{
    visible_ = false;
	inFocus_ = false;
	tex_window_ = NULL;
	name_ = name;

}




void I_cWindow::Draw(void)
{
 if (!visible_)
     return;
    
  if (tex_window_)
      SDL_RenderCopy(AndUIn::renderer_, tex_window_, NULL, &window_rect_);

  size_t count = vWidgetList.size();

	  // mozda staviti iterator. 
  for (size_t c = 0; c < count; c++)
	  {
	   I_cWidget *wdg = vWidgetList[c];
	    wdg->Draw();
	  }


}





I_cWindow::~I_cWindow()
{
 int count = GetControlCount();
 for (int c=0;c<count;c++)
     {
	  I_cWidget *wdg = vWidgetList[c];
	 
	  delete wdg;
	 }

	vWidgetList.clear();

}


void I_cWindow::Show(void)
{
  I_cObject::SetVisible(true);
  OnShow();
}


void I_cWindow::Close(void)
{
  I_cObject::SetVisible(false);
  OnClose();
}



void I_cWindow::OnShow(void)
{
 
}

void I_cWindow::OnClose(void)
{
//OnClose();
}


void I_cWindow::SetActive(bool b)
{
 I_cObject::SetActive(b);
 
 printf("WIndow: %s - focus: %d\n",name_.c_str(),b);


}

void I_cWindow::AddWidget(I_cWidget *widget)
{
 // psotavi poziciju widgeta relativno u odnosu na parent window
 SDL_Rect wdg_rect = widget->GetPos();
 widget->SetPos(window_rect_.x + wdg_rect.x, window_rect_.y + wdg_rect.y, wdg_rect.w, wdg_rect.h);

 vWidgetList.push_back(widget);
}


void I_cWindow::RemoveWidget(I_cWidget *ptr_widget)
{
 for (size_t c=0;c<vWidgetList.size();c++)
     {
      if (vWidgetList[c] == ptr_widget) 
         {
          vWidgetList.erase(vWidgetList.begin() + c);
         }
     }
}




bool I_cWindow::PointInWindowRect(SDL_Point pt)
{
 return SDL_PointInRect(&pt, &window_rect_);
}


bool I_cWindow::PointInWidgetRect(SDL_Point pt)
{
 for (size_t c=0;c<vWidgetList.size();c++)
     {
      I_cWidget *ptr = vWidgetList[c];
      if (ptr->PointInRect(pt))
          return true;
     }

 return false;
}



void I_cWindow::SetName(std::string name)
{
 name_ = name;
}


std::string I_cWindow::GetName(void)
{
 return name_;
}




int I_cWindow::GetControlCount(void)
{
 return (int)vWidgetList.size();
}

I_cWidget *I_cWindow::GetControl(int num)
{
 return vWidgetList[num];
}



I_cWidget *I_cWindow::GetControl(SDL_Event *event)
{

	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);
	SDL_Point pt = { x,y };

	size_t count = vWidgetList.size();
	for (size_t c = 0; c < count; c++)
	    {
		  I_cWidget *wdg = vWidgetList[c];

	     if (SDL_PointInRect(&pt, &wdg->widget_rect_))
		     {
		      return wdg;
			  }
	    }
 return NULL;
}



void I_cWindow::SetBackgroundTexture(SDL_Texture *tex)
{
 this->tex_window_ = tex;
}


void I_cWindow::SetActiveWidget(I_cWidget *wdg)
{
	size_t count = vWidgetList.size();
	for (size_t c = 0; c < count; c++)
	{
		I_cWidget *ptr_wdg = vWidgetList[c];
		if (ptr_wdg != wdg)
		    wdg->SetFocus(false);
			 else ptr_wdg->SetFocus(true);
	}

}



void I_cWindow::DefocusAll(void)
{
	size_t count = vWidgetList.size();
	for (size_t c = 0; c < count; c++)
	{
		I_cWidget *ptr_wdg = vWidgetList[c];
		ptr_wdg->SetFocus(false);
	}
}


void I_cWindow::SetPosition(SDL_Rect rect)
{
 window_rect_ = rect;
}


void I_cWindow::SetPosition(int x, int y, int w, int h)
{
 window_rect_ = AndUIn::GetRect(x,y,w,h);
}


void I_cWindow::HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type)
{


	switch (type)
	{
	case AndUIn::EVENT_BUTTON_UP:
	{
		// ako je button state_pressed prodji sve buttone i posalji button_up event.
		// ovo radimo jer ako je mis pritisnut i izadje iz button_rect nece se pokrenuti promjena texture u default state
		// takodjer posalji BUTTON_UP event tko god je pritisnut
		size_t count = vWidgetList.size();
		for (size_t c = 0; c < vWidgetList.size(); c++)
		{
			I_cWidget* wdg = vWidgetList[c];
			if (wdg->type_ == ANDUIN_CONTROL_BUTTON)
			{
				I_cButton* btn = (I_cButton*)wdg;
				wdg->HandleEvent(type);
			}
		}
		break;
	}

	case AndUIn::EVENT_BUTTON_DOWN:
	{
		// prodji sve objekte i postavi focus = true ako smo kliknuli na abjekt
		I_cWidget* focus = NULL;
		for (size_t c = 0; c < vWidgetList.size(); c++)
		{
			I_cWidget* wdg = vWidgetList[c];
			if (wdg->type_ == ANDUIN_CONTROL_BUTTON)
			{
				I_cButton* btn = (I_cButton*)wdg;
				wdg->HandleEvent(type);
			}
		}

		break;
	}
	}
}



SDL_Rect I_cWindow::GetRect(void)
{
 return window_rect_;
}

