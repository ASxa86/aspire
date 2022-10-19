#include <aspire/Visitor.h>

#include <aspire/Node.h>

using aspire::Visitor;

auto Visitor::visit(Node& x) -> void
{
	switch(this->traversal)
	{
		case Traversal::Descend:
			x.descend(*this);
			break;
		case Traversal::Ascend:
			x.ascend(*this);
			break;
		default:
			break;
	}
}

auto Visitor::setTraversal(Traversal x) noexcept -> void
{
	this->traversal = x;
}

auto Visitor::getTraversal() const noexcept -> Traversal
{
	return this->traversal;
}
