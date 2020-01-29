#pragma once
#include "anduin.h"
#include "I_cWidget.h"

class I_cProgressBar: public I_cWidget
{
 public:
        I_cProgressBar();
       ~I_cProgressBar();

        void SetPos(int x, int y);
        void Init(SDL_Rect pos, int max);
        void Draw(void);
        void Step(void);
        void Reset(void);
        void SetTexture(SDL_Texture *tex);


        bool using_default_color_;
        SDL_Color clr;
        int max_;
        float current_percent_;
        float step_;
                SDL_Rect progress_rect_;
 private:

        SDL_Texture *tex_background_;
          
};