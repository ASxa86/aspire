#include <aspire/gui/Window.h>
#include <aspire/core/PimplImpl.h>

using aspire::Window;

struct Window::Impl
{
};

Window::Window()
{
	Object::connect(this, &Object::initialized, this, [this] { this->onInitialized(); });
}

auto Window::onInitialized() -> void
{
}
