#include <aspire/Visitor.h>

#include <aspire/Camera.h>
#include <aspire/Geometry.h>
#include <aspire/Node.h>

using aspire::Visitor;

Visitor::Visitor(unsigned int x) : depth{x}
{
}

auto Visitor::visit(Node& x) -> void
{
	this->traverse(x);
}

auto Visitor::visit(Camera& x) -> void
{
	this->visit(static_cast<Node&>(x));
}

auto Visitor::visit(Geometry& x) -> void
{
	this->visit(static_cast<Node&>(x));
}

auto Visitor::setTraversal(Traversal x) noexcept -> void
{
	this->traversal = x;
}

auto Visitor::getTraversal() const noexcept -> Traversal
{
	return this->traversal;
}

auto Visitor::setDepth(unsigned int x) noexcept -> void
{
	this->depth = x;
}

auto Visitor::getDepth() const noexcept -> int
{
	return this->depth;
}

auto Visitor::traverse(Node& x) -> void
{
	this->depthCurrent++;

	if(this->depthCurrent <= this->depth)
	{
		switch(this->traversal)
		{
			case Traversal::Descend:
			{
				for(const auto& child : x.getChildren())
				{
					child->accept(*this);
				}
			}
			break;

			case Traversal::Ascend:
			{
				auto parent = x.getParent();

				while(parent != nullptr)
				{
					parent->accept(*this);
					parent = parent->getParent();
				}
			}
			break;

			default:
				break;
		}
	}

	this->depthCurrent--;
}
