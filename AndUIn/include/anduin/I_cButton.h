#pragma once
#include "anduin.h"
#include "I_cWidget.h"
#include "FastDelegate/FastDelegate.h"
#include <string>

using namespace fastdelegate;

class I_cButton : public I_cWidget
{
 public:
	 I_cButton(std::string nameid = "wdg_button");
	~I_cButton();

	void SetPos(int x, int y, int w, int h);
	void SetText(std::string txt, SDL_Color clr = AndUIn::White);
	virtual void Draw(void);
	bool IsPressed(void);
	void SetPressedState(bool press);
	std::string GetText();
	void SetTexture(SDL_Texture *tex_up, SDL_Texture *tex_dwn);
	void SetTexture(SDL_Texture *tex);
	void SetUserData(void *ptr_data);
	void SetUserData(int32_t data);
	void *GetUserData(void);
	int32_t GetUserDataId(void);
	void SetVisible(bool visible);
	void SetEnable(bool e);
	SDL_Texture *GetTexture(void);
	void SetShowText(bool s);
    void SetTransparent(bool b);

	typedef FastDelegate1<void *> MyDelegate;
	MyDelegate OnClick;



protected:
	void HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type);
	void RenderSkin(void);
	
	void CreateTextTexture(SDL_Color clr);

	SDL_Texture *tex_background;
	SDL_Rect rect_text_;
	std::string txt_;
	
	SDL_Texture *tex_button_up_;
	SDL_Texture *tex_button_down_;
	SDL_Texture *tex_current_;
	SDL_Texture *tex_text_;
	bool show_txt_;

	//SDL_Color txt_clr_;
	void *ptr_Data_;   // fastdelegate ce uvjek prenositi ptr_data_
	int32_t data_;

	void createUIBox(void);
	std::string m_name;
	bool custom_tex_; // da li koristimo default button skin
	bool visible_;
    bool transparent_;
	bool enabled_;



	void dummy(void *); // prilikom kreacije buttona, bindacemo onClick na ovo da ne puca program


};