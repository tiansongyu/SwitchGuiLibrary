#pragma once 
enum COLOUR
{
	FG_BLACK = 0xFF000000,
	FG_DARK_BLUE = 0xFF8B0000,
	FG_DARK_GREEN = 0xFF006400,
	FG_DARK_CYAN = 0xFF8B8B00,
	FG_DARK_RED = 0xFF00008B,
	FG_DARK_MAGENTA = 0xFF8B008B,
	FG_DARK_YELLOW = 0xFF00D7FF,
	FG_GREY = 0xFF808080, 
	FG_DARK_GREY = 0xFFA9A9A9,
	FG_BLUE = 0xFFFF0000,
	FG_GREEN = 0xFF008000,
	FG_CYAN = 0xFFFFFF00,
	FG_RED = 0xFF0000FF,
	FG_MAGENTA = 0xFFFF00FF,
	FG_YELLOW = 0xFF00FFFF,
	FG_WHITE = 0xFFFFFFFF,
};

struct KeyBoard
{
	uint32_t kDown;
	uint32_t kHeld;
	uint32_t kUp;
};

struct sMouseState
{
	bool bPressed;
	bool bReleased;
	bool bHeld;
	uint32_t mouse_pos_x;
	uint32_t mouse_pos_y;
};