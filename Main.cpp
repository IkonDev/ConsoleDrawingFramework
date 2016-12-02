#include "IkonApplication.h"

int main()
{
	IkonApplication* App = new IkonApplication();

	App->Start();

	if (App != nullptr)
		delete App;

	return 0;
}