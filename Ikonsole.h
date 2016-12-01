#pragma once

#include <Windows.h>
#include <Gdiplus.h>

using namespace Gdiplus;

class Ikonsole
{
public:
	bool Setup(unsigned int Width, unsigned int Height);

	BitmapData GetFrame();
	void DisplayFrame(BitmapData A_Data);

	~Ikonsole();

	unsigned int PixelWidth;
	unsigned int PixelHeight;

private:
	BitmapData _BitmapData;
	Bitmap*   _Buffer = nullptr;

	Gdiplus::Graphics* _Graphics = nullptr;
	ULONG_PTR          _GDI;

	HWND               _ConsoleWindow;
	HDC                _ConsoleDC;
};

