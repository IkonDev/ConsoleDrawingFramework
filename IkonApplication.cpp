#include "IkonApplication.h"
#include "Ikonsole.h"

void IkonApplication::Start()
{
	IkonConsole = new Ikonsole();
	IkonConsole->Setup(1366, 768);
	Loop();
}

void IkonApplication::Process()
{
	//Make game stuff happen
}

void IkonApplication::Draw()
{
	static unsigned long int t = 5;
	BitmapData BD = IkonConsole->GetData();
	UINT* pixels = (UINT*)BD.Scan0; 
	for (int x = 0; x < IkonConsole->PixelWidth; ++x)
	{
		for (int y = 0; y < IkonConsole->PixelHeight; ++y)
		{
			pixels[((int)y * (BD.Stride / sizeof(int)) + (int)x)] = 0xff001100 * cos(x) * cos(y) / t;
		}
	}
	if(flip)
		t *= 1.25;
	else
		t /= 1.25;
	if (t > 1000000000)
	{
		flip = false;
	}
	if (t < 5)
	{
		flip = true;
	}
}

void IkonApplication::Loop()
{
	while (true)
	{	

		IkonConsole->GetFrame();
		Process();
		Draw();

		Threadlist.push_back(std::thread(
		[this]
		()
		{
			IkonConsole->DisplayFrame();
		}
		));
		Threadlist.back().detach();
	}

	for (int i = 0; i < Threadlist.size(); ++i)
	{
		if (Threadlist[i].joinable())
			Threadlist[i].join();
	}
	Threadlist.clear();
}

void IkonApplication::End()
{
}
