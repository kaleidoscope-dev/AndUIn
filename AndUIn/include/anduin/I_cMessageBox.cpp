#include "I_cMessageBox.h"
#include "I_cLabel.h"
#include "I_cAndUIn.h"

I_cMessageBox::I_cMessageBox()
{
}


I_cMessageBox::~I_cMessageBox()
{
}


I_cMessageBox::I_cMessageBox(int x, int y, int w, int h, std::string txt, I_cWindow *parent) : I_cWindow("Message Box",x,y,w,h)
{
 SetPosition(x,y,w,h);
 //SetBackgroundTexture(gAssetManager->GetAssetTexture(ASSET_UI_WINDOW_BACKGROUND)->GetTexture());
 I_cLabel *label = new I_cLabel(AndUIn::GetRect(20,window_rect_.h/2-25,w-40,35),AndUIn::White,txt.c_str());
 AddWidget(label); 

 btn_ok_ = new I_cButton();
 btn_ok_->SetPos(window_rect_.w/2-70, window_rect_.h-30, 140,50);
 AddWidget(btn_ok_);

 //btn_ok_->SetTexture(gAssetManager->GetAssetTexture(ASSET_UI_BUTTON)->GetTexture());
 btn_ok_->SetText("  OK  ");
 btn_ok_->SetShowText(true);
 btn_ok_->OnClick.bind(this, &I_cMessageBox::OnClick_Ok);

 wnd_parent_ = parent;
 
 gAnduin->CreateAnduinWindow(this);
 gAnduin->SetActiveWindow(this);

}





void I_cMessageBox::OnClick_Ok(void *ptr_data)
{
 Close();
 wnd_parent_->SetActive(true);
 gAnduin->DeleteWindow(this);
}







void I_cMessageBox::Init(void)
{


}




void I_cMessageBox::Draw(void)
{
 I_cWindow::Draw();


}

