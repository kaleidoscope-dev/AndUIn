#pragma once
#include "I_cWidget.h"
#include "I_cObject.h"



class I_cWindow: public I_cObject
{
 public:
	 I_cWindow();
	 I_cWindow(std::string name,int x = 0, int y = 0, int w = 640, int h = 480);
	~I_cWindow();

	void SetActive(bool f);
	virtual void Draw(void);
    virtual void OnShow(void);
    virtual void OnClose(void);
	void Show(void);
	void Close(void);
	void AddWidget(I_cWidget *widget);
    void RemoveWidget(I_cWidget *ptr_widget);
	int GetControlCount(void);
	virtual void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);
	I_cWidget *GetControl(int num);  // TODO:  get widget
	I_cWidget *GetControl(SDL_Event *event);
	void SetBackgroundTexture(SDL_Texture *tex);
	void SetActiveWidget(I_cWidget *wdg);
	void DefocusAll(void);
	//void HandleEvent(SDL_Event *event);
    bool PointInWindowRect(SDL_Point pt);
    bool PointInWidgetRect(SDL_Point pt);
    void SetName(std::string name);
    void SetPosition(SDL_Rect rect);
    void SetPosition(int x, int y, int w, int h);
    std::string GetName(void);
	std::vector<I_cWidget*>vWidgetList;
	//bool GetFocus(void);
	SDL_Rect GetRect(void);


protected:   
	SDL_Texture *tex_window_;         // pozadina koju crtamo na render target
	bool modal_;


protected:
	void Init(std::string name);
};