#include <aspire/Camera.h>

using aspire::Camera;

auto Camera::accept(Visitor& x) -> void
{
	x.visit(*this);
}
