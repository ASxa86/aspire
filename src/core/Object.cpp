#include <aspire/core/Object.h>
#include <algorithm>

using aspire::core::Object;

auto Object::setName(std::string_view x) -> void
{
	this->name = x;
}

auto Object::getName() const -> std::string_view
{
	return this->name;
}

auto Object::getParent() const -> Object*
{
	return this->parent;
}

auto Object::addChild(std::unique_ptr<Object> x) -> void
{
	x->parent = this;
	this->children.emplace_back(std::move(x));
}

auto Object::remove() -> std::unique_ptr<Object>
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

auto Object::getChildren() const -> const std::vector<std::unique_ptr<Object>>&
{
	return this->children;
}
