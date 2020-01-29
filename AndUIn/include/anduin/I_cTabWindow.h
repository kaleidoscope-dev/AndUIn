#pragma once
#include "anduin.h"
#include "I_cWindow.h"
#include "I_cButton.h"
#include "I_cObject.h"

class I_cTabWindow: public I_cObject
{
 public:
     I_cTabWindow();
     I_cTabWindow(std::string name, int x = 0, int y = 0, int w = 640, int h = 480);
    virtual ~I_cTabWindow();


       //void Init(std::string name);
       void AddTab(std::string name);
       void AddTab(std::string name, I_cWindow *wnd);
       void SetTabName(int tab, std::string name);
       virtual void SelectTab(int tab);
       void Draw(void);
       virtual void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);
       I_cWindow *GetWindow(int tab);
       virtual void SetActive(bool b);
       void DeactiveAll(void);
       void AddWidget(I_cWidget *wdg);
       virtual void Show(void);
	   void Close(void);

       std::vector<I_cWindow*>vWindowList;
       std::vector<I_cButton*>vTabButtonList;


       void OnClick_Tab(void *ptr_data);
       SDL_Rect GetRect(void);

private:
         int current_selected_tab_;
         SDL_Rect window_rect_;
         std::vector<I_cWidget*>vWidgetList;
};