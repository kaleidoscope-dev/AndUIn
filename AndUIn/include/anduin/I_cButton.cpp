#include "I_cButton.h"
#include <string>


I_cButton::I_cButton(std::string nameid)
{
 custom_tex_ = false;
 ptr_Data_ = NULL;
 visible_ = true;
 enabled_ = true;
 OnClick.bind(this, &I_cButton::dummy);
 type_ = ANDUIN_CONTROL_BUTTON;

 tex_text_ = NULL;
 tex_current_ = NULL;
 tex_background = NULL;
 tex_button_down_ = NULL;
 tex_button_up_ = NULL;
 show_txt_ = true;
 ptr_Data_ = NULL;
 data_ = -1;
 I_cWidget::nameId_ = "wdg_button";
 m_name = nameid;
 transparent_ = false;
}



I_cButton::~I_cButton()
{
 SDL_DestroyTexture(tex_text_);


 // NOTE: zasto mi ovdje brisemo user data!!???
 // TOOD: remove
 //if (ptr_Data_)
 //    delete ptr_Data_;
}




void I_cButton::SetText(std::string txt, SDL_Color clr)
{
 txt_ = txt;
 CreateTextTexture(clr);

 // text je uvijek na sredini
// int htx = (rect_text_.w / 2) - (AndUIn::font_size_ / 2);
// int hrx = widget_rect_.w / 2;

 //rect_text_.x = widget_rect_.x + (hrx - htx) - AndUIn::font_size_ / 2;
}



void I_cButton::SetShowText(bool s)
{
 show_txt_ = s;
}






void I_cButton::Draw(void)
{
 // crtamo samo ako smo vidljivi
 if (!visible_)
 	 return;

 // ako smo transparentni, ne crtamo button, ali procesiramo evente
 if (!transparent_)
    {
     RenderSkin();

     SDL_Rect rc = widget_rect_;

	 if (show_txt_)
	    {
         if (tex_text_)
			 SDL_RenderCopy(AndUIn::renderer_, tex_text_, NULL, &rect_text_);
		 //if (tex_text_)
			 //SDL_RenderCopy(AndUIn::renderer_, tex_text_, NULL, &widget_rect_);
	 }

    }

	
	    

 I_cWidget::Draw();
}



bool I_cButton::IsPressed(void)
{
 if (tex_current_ == tex_button_down_)
	return true;

 return false;
}


void I_cButton::SetPressedState(bool press)
{
 if (press)
    {
	 tex_current_ = tex_button_down_;
	}else tex_current_ = tex_button_up_;
}

std::string I_cButton::GetText()
{
	return txt_;
}


void I_cButton::SetTexture(SDL_Texture *tex_up, SDL_Texture *tex_dwn)
{
 tex_button_up_ = tex_up;
 tex_button_down_ = tex_dwn;
 tex_current_ = tex_button_up_;
 custom_tex_ = true;
}


void I_cButton::SetTexture(SDL_Texture *tex)
{
 tex_button_up_ = tex;
 tex_button_down_ = tex;
 tex_current_ = tex_button_up_;
 custom_tex_ = true;
}



void I_cButton::RenderSkin(void)
{

	if (!custom_tex_)
       {
		 int x, y, x1, y1;
		 x = widget_rect_.x, y = widget_rect_.y;
		 x1 = widget_rect_.x + widget_rect_.w, y1 = widget_rect_.y + widget_rect_.h;

		 roundedBoxRGBA(AndUIn::renderer_, x+1, y, x1-1, y1, 2, 125, 125, 125, 255);  // prvi sloj (pozadina)
		 roundedBoxRGBA(AndUIn::renderer_, x+1, y, x1-1, y1-1, 2, 0, 0, 0, 255);
		 lineRGBA(AndUIn::renderer_, x+3 , y+2 , x1-3, y+2 , 125, 125, 125, 255);
		}

	SDL_RenderCopy(AndUIn::renderer_, tex_current_, NULL, &widget_rect_);
}






void I_cButton::HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type)
{
 // procesiramo evente samo ako smo vidljivi
 if (!visible_)
     return;

 if (!enabled_)
     return;

	int x = 0, y = 0;
	//SDL_GetMouseState(&x, &y);
	SDL_Point pt = { AndUIn::mouse_x,AndUIn::mouse_y };


	switch (type)
	{
	case AndUIn::EVENT_BUTTON_DOWN:
		if (SDL_PointInRect(&pt, &widget_rect_))
		{ 
			tex_current_ = tex_button_down_;
		}//else focus_ = false;
		break;

	case AndUIn::EVENT_BUTTON_UP:
		tex_current_ = tex_button_up_;
		if (SDL_PointInRect(&pt, &widget_rect_))
		{

		 OnClick(ptr_Data_);
		}

		break;

	}

}



void I_cButton::SetPos(int x, int y, int w, int h)
{

	I_cWidget::SetPos(x,y,w,h);
	
	//rect_text_.x = x;
	//rect_text_.y = y + h;
	//rect_text_.w = w - AndUIn::font_size_;
	//rect_text_.h = h/2;

	if (!custom_tex_)
	   createUIBox();
}


// Button texture, pressed, released
void I_cButton::createUIBox(void)
{

	SDL_Surface *up_surface = SDL_CreateRGBSurface(0, widget_rect_.w, widget_rect_.h, 32, 0, 0, 0, 0);
	SDL_Surface *down_surface = SDL_CreateRGBSurface(0, widget_rect_.w, widget_rect_.h, 32, 0, 0, 0, 0);

	SDL_Color c1 = { 72,72,72,255 };
	SDL_Color c2 = { 60,60,60,255 };

	tex_button_up_ = vertgradient(up_surface, c1, c2);

	SDL_Color c3 = { 36,36,36,255 };
	SDL_Color c4 = { 29,29,29,255 };

	tex_button_down_ = vertgradient(down_surface, c3, c4);

	tex_current_ = tex_button_up_;

	SDL_FreeSurface(up_surface);
	SDL_FreeSurface(down_surface);

}

void I_cButton::dummy(void *)
{
}

void I_cButton::SetUserData(void *ptr_data)
{
 ptr_Data_ = ptr_data;
}

void I_cButton::SetUserData(int32_t data)
{
 data_ = data;
}


void *I_cButton::GetUserData(void)
{
 return ptr_Data_;
}

int32_t I_cButton::GetUserDataId(void)
{
 return data_;
}


// crta/ ne crta
void I_cButton::SetVisible(bool visible)
{
 visible_ = visible;
}

// procesira event/ ne procesira event
void I_cButton::SetEnable(bool e)
{
 enabled_ = e;
}

void I_cButton::SetTransparent(bool b)
{
 transparent_ = b;
}




void I_cButton::CreateTextTexture(SDL_Color clr)
{


	SDL_Color white = { 0xFF, 0xFF, 0xFF };
	SDL_Color black = { 0x00, 0x00, 0x00 };

	

	SDL_Surface *bg_surface = TTF_RenderText_Blended(AndUIn::font_ol_, txt_.c_str(), black);
	SDL_Surface *fg_surface = TTF_RenderText_Blended(AndUIn::font_, txt_.c_str(), clr);
	SDL_Rect rect = { FONT_OUTLINE_SIZE, FONT_OUTLINE_SIZE, bg_surface->w-4, bg_surface->h-4};

	//rect.x += 20;

	SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);


	tex_text_ = SDL_CreateTextureFromSurface(AndUIn::renderer_, bg_surface);

	
	

	rect_text_.x = widget_rect_.x + AndUIn::GetPercentage(widget_rect_.w,10);
	rect_text_.y = widget_rect_.y + AndUIn::GetPercentage(widget_rect_.h,25);
	rect_text_.w = widget_rect_.w - AndUIn::GetPercentage(widget_rect_.w,20);
	rect_text_.h = widget_rect_.h -AndUIn::GetPercentage(widget_rect_.h,50); 


	//rect_text_.w = (int)txt_.length() * AndUIn::font_size_;  // TODO: define velicina slova

	SDL_FreeSurface(bg_surface);
	SDL_FreeSurface(fg_surface);


}








SDL_Texture *I_cButton::GetTexture(void)
{
 return tex_current_;
}



