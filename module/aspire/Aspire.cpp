#include <aspire/Aspire.h>

using aspire::Aspire;

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
aspire::Meters Aspire::meters(double x) const noexcept
{
	return Meters{x};
}
