#include <aspire/Node.h>

using aspire::Node;

Node::Node(std::string_view x) : name{x}
{
}

auto Node::setName(std::string_view x) -> void
{
	this->name = x;
}

auto Node::getName() const noexcept -> std::string_view
{
	return this->name;
}

auto Node::getParent() const noexcept -> Node*
{
	return this->parent;
}

auto Node::addChild(std::unique_ptr<Node> x) -> void
{
	x->parent = this;
	this->children.emplace_back(std::move(x));
}

auto Node::getChildren() const -> const std::vector<std::unique_ptr<Node>>&
{
	return this->children;
}
