#include <aspire/core/Object.h>

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

auto Object::remove() -> void
{
	if(this->parent == nullptr)
	{
		return;
	}

	std::erase_if(this->parent->children, [this](auto&& x) { return x.get() == this; });
}

auto Object::getChildren() const -> const std::vector<std::unique_ptr<Object>>&
{
	return this->children;
}
