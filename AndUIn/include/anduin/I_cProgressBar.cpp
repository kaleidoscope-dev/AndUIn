#include "I_cProgressBar.h"
//#include "gameapi.h"

I_cProgressBar::I_cProgressBar()
{
 current_percent_ = 0;
 step_ = 1;
 max_ = 100;
 using_default_color_ = true;
 tex_background_ = NULL;
}


void I_cProgressBar::SetPos(int x, int y)
{
 widget_rect_.x = x;
 widget_rect_.y = y;
 progress_rect_.x = x;
 progress_rect_.y = y;
}


I_cProgressBar::~I_cProgressBar()
{
}


void I_cProgressBar::Init(SDL_Rect pos, int max)
{
 max_= max;
 current_percent_ = 100;
 widget_rect_ = pos;
 progress_rect_ = AndUIn::GetRect(pos.x + 4,pos.y +4,pos.w-10,pos.h-10);

 step_ = (float)100/(float)max;

}



void I_cProgressBar::SetTexture(SDL_Texture *tex)
{
 tex_background_ = tex;
}


void I_cProgressBar::Step(void)
{
 if (current_percent_ > 0)
     current_percent_ -= step_;
}


void I_cProgressBar::Reset(void)
{
 current_percent_ = 100;
 progress_rect_.w = widget_rect_.w;
}


void I_cProgressBar::Draw()
{

 if (tex_background_)
    {
     SDL_RenderCopy(AndUIn::renderer_,tex_background_,0,&widget_rect_);
    }


 //SDL_Rect bar_rect = AndUIn::GetRect(widget_rect_.x+3,widget_rect_.y+3,widget_rect_.w-6,widget_rect_.h-8);


 //AndUIn::BoxRGBA(progress_rect_,AndUIn::GetColor(0,0,0));

 
 progress_rect_.w = AndUIn::GetPercentage(widget_rect_.w-10,(int)current_percent_);

 int g = AndUIn::GetPercentage(255,(int)current_percent_);
 int r = AndUIn::GetPercentage(255,(int)current_percent_);

 if (using_default_color_)
     AndUIn::BoxRGBA(progress_rect_,AndUIn::GetColor(255-r,g,0));
     else  AndUIn::BoxRGBA(progress_rect_,clr);
   

}