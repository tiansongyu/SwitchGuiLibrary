#include <switch.h>
#include <stdio.h>
#include <memory.h>

#include "guis/gui_main.hpp"
#include "guis/gui_about.hpp"

#define FB_WIDTH 1280
#define FB_HEIGHT 720

int main()
{
	framebufferCreate(&Gui::g_fb_obj, nwindowGetDefault(), FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBA_8888, 2);
	framebufferMakeLinear(&Gui::g_fb_obj);

	Gui *curr_gui;
	int last_index  = -1;
	u64 kDown;
	int index = 1;
	while (appletMainLoop())
	{
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if(last_index!=index)
			if(curr_gui!=nullptr)
				delete curr_gui;
			switch (index)
			{
			case 2:
				curr_gui = new GuiMain();
				break;
			case 1:
				curr_gui = new GuiAbout();
				break;
			default:
				break;
			}
		last_index = index;
		if (kDown & KEY_A)
		{
			index++;
			if (index > 2)
				index = 1;
		}
		
		if (curr_gui != nullptr)
		{
			curr_gui->Draw();
		}
	}

	return 0;
}