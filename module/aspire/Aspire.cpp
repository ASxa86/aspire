#include <aspire/Aspire.h>

using aspire::Aspire;

aspire::Meters Aspire::meters(double x) const noexcept
{
	return Meters{x};
}
