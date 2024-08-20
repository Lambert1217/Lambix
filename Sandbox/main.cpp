#include "Debug/lbLog.h"
#include "Window/lbWindow.h"

int main()
{
	Lambix::lbLog::init();
	LOG_INFO("你好,Lambix！");

	WINDOW->init(960,720,"Sandbox");

	while(!WINDOW->shouldClose()){
		WINDOW->pollEvents();
		WINDOW->swapBuffer();
	}

	WINDOW->destroy();
	return 0;
}
