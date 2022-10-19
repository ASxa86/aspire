#include <aspire/Geometry.h>

using aspire::Geometry;

auto Geometry::accept(Visitor& x) -> void
{
	x.visit(*this);
}
