#include <iostream>

#include <P2/Application.h>

int main(int argc, char** argv) {
	Application app;

	Application::SetApplication(&app);

	if (!app.Init()) {
		return -1;
	}

	app.Run();

	app.Cleanup();

	return 0;
}