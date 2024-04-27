#include <aspire/scene/Node.h>
#include <algorithm>

using aspire::scene::Node;

auto Node::addChild(std::unique_ptr<Node> x) -> void
{
	x->parent = this;
	this->children.emplace_back(std::move(x));
}

auto Node::getChildren() const noexcept -> const std::vector<std::unique_ptr<Node>>&
{
	return this->children;
}

auto Node::getParent() const noexcept -> Node*
{
	return this->parent;
}

auto Node::remove() -> std::unique_ptr<Node>
{
	if(this->parent == nullptr)
	{
		return nullptr;
	}

	auto [beg, end] = std::ranges::remove_if(this->parent->children, [this](auto&& x) { return x.get() == this; });

	if(beg == end)
	{
		return nullptr;
	}

	auto node = std::move(*beg);
	this->parent->children.erase(beg, end);
	node->parent = nullptr;

	return node;
}
