#include <aspire/core/Kernel.h>

using aspire::Kernel;

auto Kernel::run() -> int
{
	this->running = true;

	this->initialize();

	while(this->running == true)
	{
		// Process events.
		// switch(type)
		// case Event::Quit:
		//	this->quit();

		// Process timers
		// variable loop // user input
		// fixed loop // physics

		// Process Graphics
		// graphics loop // vsync
		this->frame.emit();
	}

	this->terminate();

	return EXIT_SUCCESS;
}

auto Kernel::quit() -> void
{
	this->running = false;
}