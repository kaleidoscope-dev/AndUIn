#pragma once
#include "anduin.h"

class I_cObject
{
 public:
        I_cObject();
       virtual ~I_cObject();


       virtual void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);
       virtual void Draw(void);
       bool GetFocus(void);
       virtual void SetActive(bool b);
       virtual void SetVisible(bool b);
       virtual bool GetVisible(void);



 protected:
       std::string name_;
       SDL_Rect window_rect_;
       bool inFocus_;
       bool visible_;
};