#include <aspire/Node.h>

using aspire::Node;

void Node::accept(Visitor& x)
{
	x.visit(*this);
}

void Node::setName(std::string_view x)
{
	this->name = x;
}

std::string_view Node::getName() const noexcept
{
	return this->name;
}
