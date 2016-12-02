#pragma once

#include <thread>
#include <vector>

class Ikonsole;
class IkonApplication
{
public:
	void Start();
	void Process();
	void Draw();
	void Loop();
	void End();

private:
	Ikonsole* IkonConsole;
	std::vector<std::thread> Threadlist;
	static unsigned int t;
	bool flip = false;
};

