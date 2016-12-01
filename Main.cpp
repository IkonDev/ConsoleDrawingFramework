#include "Ikonsole.h"
#include <thread>
#include <vector>
int main()
{
	Ikonsole IC = Ikonsole();
	IC.Setup(800, 600);
	int x = 0;
	BitmapData BD = IC.GetFrame();

	IC.DisplayFrame(BD);
	UINT* pixels = (UINT*)BD.Scan0;

	std::vector<std::thread> Threadlist;

	while (x < 600)
	{
		x++;

		pixels[(x * (BD.Stride / sizeof(int)) + (int)20)] = 0xffAA0000;
		pixels[(x * (BD.Stride / sizeof(int)) + (int)21)] = 0xff00AA00;
		pixels[(x * (BD.Stride / sizeof(int)) + (int)22)] = 0xff0000AA;

		Threadlist.push_back(std::thread(
		[&IC, &BD]
		() 
		{
			IC.DisplayFrame(BD);
		}
		));
		Threadlist.back().detach();
	}

	for(int i = 0; i < Threadlist.size(); ++i)
	{
		if(Threadlist[i].joinable())
			Threadlist[i].join();
	}
	Threadlist.clear();

	return 0;
}