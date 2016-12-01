#include "Ikonsole.h"


bool Ikonsole::Setup(unsigned int Width, unsigned int Height)
{
	//Set window size.
	PixelWidth = Width;
	PixelHeight = Height;

	//Create GDI & Startup
	GdiplusStartup(&_GDI, &GdiplusStartupInput(), NULL);

	//Get a console handle
	_ConsoleWindow = GetConsoleWindow();
	_ConsoleDC = GetDC(_ConsoleWindow);
	_Graphics = new Gdiplus::Graphics(_ConsoleDC);

	return true;
}

//Returns a bitlocked frame
BitmapData Ikonsole::GetFrame()
{
	//Return backbuffer bitmapdata
	if (_Buffer != nullptr)
	{
		delete _Buffer;
		_Buffer = nullptr;
	}
	_Buffer = new Bitmap(PixelWidth, PixelHeight, PixelFormat32bppARGB);
	_Buffer->LockBits(&Rect(0, 0, PixelWidth, PixelHeight), ImageLockModeWrite, PixelFormat32bppARGB, &_BitmapData);
	return _BitmapData;
}

void Ikonsole::DisplayFrame(BitmapData A_Data)
{
	_Buffer->UnlockBits(&A_Data);
	_Graphics->DrawImage(_Buffer, Rect(0, 0, PixelWidth, PixelHeight));
}

Ikonsole::~Ikonsole()
{
	//Release GDI
	_Graphics->ReleaseHDC(_ConsoleDC);

	//Delete _Graphics
	if (_Graphics != nullptr)
	{
		delete _Graphics;
		_Graphics = nullptr;
	}

	//Delete _BitMapA/B
	if (_Buffer != nullptr)
	{
		delete _Buffer;
		_Buffer = nullptr;
	}
}
