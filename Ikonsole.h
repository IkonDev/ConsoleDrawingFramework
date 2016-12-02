#pragma once

#include <Windows.h>
#include <Gdiplus.h>
#include <mutex>

using namespace Gdiplus;

class Ikonsole
{
public:
	bool Setup(unsigned int Width, unsigned int Height);

	BitmapData GetFrame();
	void DisplayFrame();
	BitmapData& GetData() { return _BitmapData; }

	~Ikonsole();

	unsigned int PixelWidth;
	unsigned int PixelHeight;

private:
	BitmapData _BitmapData;
	bool AreBitsLocked = false;
	Bitmap*   _Buffer = nullptr;

	Gdiplus::Graphics* _Graphics = nullptr;
	ULONG_PTR          _GDI;

	HWND               _ConsoleWindow;
	HDC                _ConsoleDC;

	std::mutex DisplayLock;
};

