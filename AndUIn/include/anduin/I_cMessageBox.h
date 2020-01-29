#pragma once
#include "AndUIn.h"
#include "I_cWindow.h"
#include "I_cButton.h"


// Panel je Text box sa slikom i mogucnosti bojanja pojedinih slova



class I_cMessageBox : public I_cWindow
{
 public:
	 I_cMessageBox();
	~I_cMessageBox();
     I_cMessageBox(int x, int y, int w, int h, std::string txt, I_cWindow *parent);

      void Init(void);
      void Draw(void);
      void OnClick_Ok(void *ptr_data);

      I_cButton *btn_ok_;
      I_cWindow *wnd_parent_;

};