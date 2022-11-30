#include <aspire/PrimitiveDrawArrays.h>

using aspire::PrimitiveDrawArrays;

PrimitiveDrawArrays::PrimitiveDrawArrays(Primitive::Type type, int first, int count) : Primitive{type}, first{first}, count{count}
{
}

auto PrimitiveDrawArrays::setFirst(int x) -> void
{
	this->first = x;
}

auto PrimitiveDrawArrays::getFirst() const -> int
{
	return this->first;
}

auto PrimitiveDrawArrays::setCount(int x) -> void
{
	this->count = x;
}

auto PrimitiveDrawArrays::getCount() const -> int
{
	return this->count;
}

auto PrimitiveDrawArrays::draw() -> void
{
	glDrawArrays(static_cast<GLenum>(this->getType()), static_cast<GLint>(this->first), static_cast<GLsizei>(this->count));
}
