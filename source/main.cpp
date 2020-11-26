#include <switch.h>
#include <stdio.h>
#include <memory.h>

#include "guis/gui_main.hpp"
#include "guis/gui_about.hpp"

#include "type.hpp"

#define FB_WIDTH 1280
#define FB_HEIGHT 720

int main()
{
	Result rc = plInitialize(PlServiceType_User);
	if (R_FAILED(rc))
		fatalThrow(rc);

	framebufferCreate(&Gui::g_fb_obj, nwindowGetDefault(), FB_WIDTH, FB_HEIGHT, PIXEL_FORMAT_RGBA_8888, 2);
	framebufferMakeLinear(&Gui::g_fb_obj);

	//keyboard
	KeyBoard keystate;
	
	//mouse
	touchPosition* touch = new touchPosition[5];
	uint32_t touch_count = 0;
	sMouseState* m_mouse = new sMouseState[5];
	uint32_t prev_touchcount = 0;

	memset(touch,0x0,5 * sizeof(touchPosition));
	memset(m_mouse , 0x0,5* sizeof(sMouseState));

	Gui *curr_gui = new GuiMain();
	int last_index = -1;
	int index = 1;
	
	while (appletMainLoop())
	{
		hidScanInput();
		keystate.kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		keystate.kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);
		keystate.kUp = hidKeysUp(CONTROLLER_P1_AUTO);
		
		/*****************************************************************/
		//touch input
		touch_count = hidTouchCount();
		//不知道当touch_count大于0时代表的值是什么，所以先处理0⑧
		//当抬起时，touch_count为零，此时不能进入for循环，所以写在循环之外
		if (touch_count == 0 && prev_touchcount > 0)
			m_mouse[0].bReleased = true;
		else
			m_mouse[0].bReleased = false;
		if (touch_count != 0 || prev_touchcount != 0)
		{
			for (u32 i = 0; i < touch_count; i++)
			{
				//update pos
				hidTouchRead(&touch[i], i);
				if (touch[i].px >= 0 && touch[i].px < 1280)
					m_mouse[i].mouse_pos_x = touch[i].px;
				if (touch[i].py >= 0 && touch[i].py < 720)
					m_mouse[i].mouse_pos_y = touch[i].py;
				//end
				if (prev_touchcount == 0 && touch_count > 0)
				{
					m_mouse[i].bPressed = true;
					m_mouse[i].bHeld = false;
					m_mouse[i].bReleased = false;
				}
				else if (prev_touchcount > 0 && touch_count > 0)
				{
					m_mouse[i].bPressed = false;
					m_mouse[i].bHeld = true;
					m_mouse[i].bReleased = false;
				}
			}
		}
		/*****************************************************************/
		
		if (last_index != index)
		{
			if (curr_gui != nullptr)
				delete curr_gui;
			switch (index)
			{
			case 1:
				curr_gui = new GuiMain();
				break;
			case 2:
				curr_gui = new GuiAbout();
				break;
			}
		}
		last_index = index;
		if (keystate.kDown & KEY_A)
		{
			index++;
			if (index > 2)
				index = 1;
		}

		if (curr_gui != nullptr)
		{
			curr_gui->OnKeyBoardInput(keystate);
			curr_gui->OnMouseInput(m_mouse);
			curr_gui->Draw();
		}
		prev_touchcount = touch_count;
	}
	plExit();

	return 0;
}