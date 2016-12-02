#include "Ikonsole.h"
#include <iostream>


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
	DisplayLock.lock();

	//Return backbuffer bitmapdata
	if (_Buffer != nullptr)
	{
		delete _Buffer;
		_Buffer = nullptr;
	}
	_Buffer = new Bitmap(PixelWidth, PixelHeight, PixelFormat32bppARGB);
	if (!AreBitsLocked)
	{
		_Buffer->LockBits(&Rect(0, 0, PixelWidth, PixelHeight), ImageLockModeWrite, PixelFormat32bppARGB, &_BitmapData);
		AreBitsLocked = true;
	}

	DisplayLock.unlock();

	return _BitmapData;
}

void Ikonsole::DisplayFrame()
{
	DisplayLock.lock();

	BitmapData _BitData = _BitmapData;
	if (AreBitsLocked)
	{
		_Buffer->UnlockBits(&_BitData);
		AreBitsLocked = false;
	}
	else
	{
		std::cout << "BITS ARE NOT LOCKED!";
	}
	_Graphics->DrawImage(_Buffer, Rect(0, 0, PixelWidth, PixelHeight));

	DisplayLock.unlock();
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
