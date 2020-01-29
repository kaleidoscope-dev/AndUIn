#pragma once
#include "anduin.h"
#include "I_cWidget.h"
#include <string>


class I_cLabel : public I_cWidget
{
 public:
	 I_cLabel();
	 I_cLabel(SDL_Rect pos, SDL_Color clr, std::string txt);
	~I_cLabel();

	void SetPos(int x, int y, int w, int h);
	void SetText(SDL_Color clr, const char *format, ...);
    int RenderTextClr(SDL_Color clr, int size, const char *format, ...);

	std::string GetText(void);
	void Draw(void);

private:
	void RenderSkin(void);
    SDL_Texture *GetStringTexture(std::string txt, SDL_Color clr);

	//void HandleEvent(SDL_Event &event);
	SDL_Texture *tex_background;
	SDL_Texture *tex_text_;
	SDL_Rect location_;
	SDL_Color color_;
	bool custom_tex_;
	std::string txt_;
	void createUIBox(void);




};