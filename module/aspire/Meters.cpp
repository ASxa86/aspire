#include <aspire/Meters.h>

using aspire::Meters;

Meters::Meters(double x) noexcept : value{x}
{
}

double Meters::toDouble() const noexcept
{
	return this->value;
}

QString Meters::toString() const
{
	return QString::number(this->value);
}
