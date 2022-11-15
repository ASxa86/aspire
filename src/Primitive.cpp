#include <aspire/Primitive.h>

using aspire::Primitive;

Primitive::Primitive(Type x) : type{x}
{
}

auto Primitive::getType() const -> Type
{
	return this->type;
}
