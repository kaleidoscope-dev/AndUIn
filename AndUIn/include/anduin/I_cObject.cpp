#include "I_cObject.h"



I_cObject::I_cObject()
{
}


I_cObject::~I_cObject()
{
}



void I_cObject::HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type)
{
}


void I_cObject::Draw(void)
{
}


bool I_cObject::GetFocus(void)
{
 return inFocus_;
}



void I_cObject::SetActive(bool b)
{
 inFocus_ = b;
}


bool I_cObject::GetVisible(void)
{
 return visible_;
}



void I_cObject::SetVisible(bool b)
{
  visible_ = b;
}
