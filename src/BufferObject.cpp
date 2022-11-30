#include <aspire/BufferObject.h>

using aspire::BufferObject;

BufferObject::~BufferObject()
{
}

auto BufferObject::setUsage(Usage x) -> void
{
	this->usage = x;
}

auto BufferObject::getUsage() const -> Usage
{
	return this->usage;
}
