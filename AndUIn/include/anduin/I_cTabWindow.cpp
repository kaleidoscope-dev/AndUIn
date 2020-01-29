//#include "gameapi.h"
#include "I_cTabWindow.h"
//#include "I_cAssetmanager.h"


I_cTabWindow::I_cTabWindow()
{
}


I_cTabWindow::~I_cTabWindow()
{
 for (size_t c=0;c<vWindowList.size();c++)
     {
      I_cWindow *ptr_window = vWindowList[c];
      delete ptr_window;
     }

 for (size_t c=0;c<vTabButtonList.size();c++)
     {
      I_cButton *ptr_button = vTabButtonList[c];
      delete ptr_button;
     }
 
 for (size_t c=0;c<vWidgetList.size();c++)
     {
      I_cWidget *ptr_widget = vWidgetList[c];
      delete ptr_widget;
     }

 
}



void I_cTabWindow::Show(void)
{
  I_cObject::SetVisible(true);
  
}


void I_cTabWindow::Close(void)
{
  I_cObject::SetVisible(false);
}



I_cTabWindow::I_cTabWindow(std::string name, int x, int y, int w, int h) 
{
    window_rect_.x = x;
    window_rect_.y = y;
    window_rect_.w = w;
    window_rect_.h = h;
    name_ = name;
    current_selected_tab_ = -1;
}



void I_cTabWindow::SetActive(bool b)
{
 I_cObject::SetActive(b);

 // postavi sve neaktivne
 for (size_t c=0;c<vWindowList.size();c++)
     {
      I_cWindow *ptr_window = vWindowList[c];
      ptr_window->SetActive(false);
     }


 if (current_selected_tab_ >= 0)
    vWindowList[current_selected_tab_]->SetActive(b);
}



void I_cTabWindow::DeactiveAll(void)
{
    for (size_t c=0;c<vWindowList.size();c++)
    {
        vWindowList[c]->SetActive(false);
    }

}



void I_cTabWindow::SetTabName(int tab, std::string name)
{
    I_cButton* btn_tab = vTabButtonList[tab];
    btn_tab->SetText(name,AndUIn::White);
}


// Dodaj novi tab na kraju zadnjeg
void I_cTabWindow::AddTab(std::string name)
{
 int bt_w = AndUIn::GetPercentage(GetRect().w, 10);
 int bt_h =  50;

 int btn_count = (int)vTabButtonList.size();
 //I_cButton *ptr_prev_button = vTabButtonList[btn_count-1];

 //SDL_Rect btn_rect = { btn_count*bt_w+10,window_rect_.h,bt_w,bt_h };
 SDL_Rect btn_rect = { (window_rect_.x + (bt_w * btn_count)),window_rect_.y + window_rect_.h,bt_w-10,bt_h };

 I_cButton* btn_tab = new I_cButton(name);
 btn_tab->SetPos(btn_rect.x, btn_rect.y, btn_rect.w, btn_rect.h);
 btn_tab->SetText(name, AndUIn::White);
 btn_tab->SetShowText(true);
 int *id = new int;
 *id = btn_count;
 btn_tab->SetUserData(id);
 btn_tab->OnClick.bind(this,&I_cTabWindow::OnClick_Tab);

 
 I_cWindow* window = new I_cWindow("Tab Window X", window_rect_.x, window_rect_.y, window_rect_.w, window_rect_.h);
 
 vWindowList.push_back(window);
 vTabButtonList.push_back(btn_tab);
}


void I_cTabWindow::AddTab(std::string name, I_cWindow *wnd)
{
    int bt_w = AndUIn::GetPercentage(GetRect().w, 15);
    int bt_h = 50;

    int btn_count = (int)vTabButtonList.size();

    SDL_Rect btn_rect = { (window_rect_.x + (bt_w * btn_count)),window_rect_.y + window_rect_.h,bt_w-10,bt_h };

    I_cButton* btn_tab = new I_cButton(name);
    btn_tab->SetPos(btn_rect.x+50, btn_rect.y, btn_rect.w, btn_rect.h);
    //btn_tab->SetTexture(gAssetManager->GetAssetTexture(ASSET_UI_BUTTON)->GetTexture(),gAssetManager->GetAssetTexture(ASSET_UI_BUTTON)->GetTexture());
    btn_tab->SetText(name, AndUIn::White);

    int* id = new int;
    *id = btn_count;
    btn_tab->SetUserData(id);
    btn_tab->OnClick.bind(this, &I_cTabWindow::OnClick_Tab);

    vWindowList.push_back(wnd);
    vTabButtonList.push_back(btn_tab);
    
    current_selected_tab_ = (int)vWindowList.size() - 1;
}



void I_cTabWindow::SelectTab(int tab)
{
 vWindowList[current_selected_tab_]->SetActive(false);
 vWindowList[current_selected_tab_]->Close();

 current_selected_tab_ = tab;
 vWindowList[current_selected_tab_]->SetActive(true);
 vWindowList[current_selected_tab_]->Show();
}






void I_cTabWindow::Draw(void)
{
 if (current_selected_tab_ >= 0)
    {
     I_cWindow* ptr_window = vWindowList[current_selected_tab_];
         ptr_window->Draw();
     //if (ptr_window->GetFocus())
    }

 for (size_t c=0;c<vTabButtonList.size();c++)
     {
      I_cButton *ptr_button = vTabButtonList[c];
      ptr_button->Draw();
     }

 
 for (size_t c = 0; c < vWidgetList.size(); c++)
     {
      I_cButton *wdg = (I_cButton*)vWidgetList[c];
      wdg->Draw();
     }

}






void I_cTabWindow::HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type)
{
    // handla evente za Tab Control Window
    switch (type)
    {
     case AndUIn::EVENT_BUTTON_UP:
     {
        // ako je button state_pressed prodji sve buttone i posalji button_up event.
        // ovo radimo jer ako je mis pritisnut i izadje iz button_rect nece se pokrenuti promjena texture u default state
        // takodjer posalji BUTTON_UP event tko god je pritisnut
        size_t count = vTabButtonList.size();
        for (size_t c = 0; c < vTabButtonList.size(); c++)
        {
            I_cWidget* wdg = vTabButtonList[c];
            if (wdg->type_ == ANDUIN_CONTROL_BUTTON)
            {
                I_cButton* btn = (I_cButton*)wdg;
                wdg->HandleEvent(type);
            }
        }


        for (size_t c = 0; c < vWidgetList.size(); c++)
        {
            I_cWidget *wdg = vWidgetList[c];
            wdg->HandleEvent(type);
        }

        break;
     }

    case AndUIn::EVENT_BUTTON_DOWN:
    {
        // prodji sve objekte i postavi focus = true ako smo kliknuli na abjekt
        I_cWidget* focus = NULL;
        for (size_t c = 0; c < vTabButtonList.size(); c++)
        {
            I_cWidget* wdg = vTabButtonList[c];
            if (wdg->type_ == ANDUIN_CONTROL_BUTTON)
            {
                I_cButton* btn = (I_cButton*)wdg;
                wdg->HandleEvent(type);
            }
        }

        for (size_t c = 0; c < vWidgetList.size(); c++)
        {
            I_cWidget *wdg = vWidgetList[c];
            wdg->HandleEvent(type);
        }


        break;
    }
    }

    // handle events za trenutno prikazani prozor
    if (current_selected_tab_ >= 0)
       {
        vWindowList[current_selected_tab_]->HandleEvent(type);
       }


}






I_cWindow* I_cTabWindow::GetWindow(int tab)
{
 return vWindowList[tab];
}



SDL_Rect I_cTabWindow::GetRect(void)
{
 return window_rect_;
}



void I_cTabWindow::AddWidget(I_cWidget *wdg)
{
    // psotavi poziciju widgeta relativno u odnosu na parent window
    SDL_Rect wdg_rect = wdg->GetPos();
    wdg->SetPos(window_rect_.x + wdg_rect.x, window_rect_.y + wdg_rect.y, wdg_rect.w, wdg_rect.h);

    vWidgetList.push_back(wdg);
}



void I_cTabWindow::OnClick_Tab(void* ptr_data)
{
    int *id = (int*)ptr_data;
    current_selected_tab_ = *id;
    vWindowList[current_selected_tab_]->SetActive(true);

    //GAMEAPI::CallEvent(GAMEAPI_EVENT_TAB_SELECTION_CHANGED,id);
}

