#include <aspire/core/Object.h>
#include <aspire/core/PimplImpl.h>
#include <algorithm>

using aspire::core::Object;

struct Object::Impl
{
	std::vector<std::unique_ptr<Object>> children;
	Object* parent{};
	std::string name;
	bool isStartup{false};
};

Object::Object() = default;
Object::~Object() = default;

auto Object::setName(std::string_view x) -> void
{
	this->pimpl->name = x;
}

auto Object::getName() const -> std::string_view
{
	return this->pimpl->name;
}

auto Object::getParent() const -> Object*
{
	return this->pimpl->parent;
}

auto Object::addChild(std::unique_ptr<Object> x) -> void
{
	if(x == nullptr)
	{
		return;
	}

	auto* temp = x.get();
	x->pimpl->parent = this;
	this->pimpl->children.emplace_back(std::move(x));

	// Once the object has been started, we need to invoke any new objects that get added dynamically after the fact.
	if(this->isStartup() == true && temp->isStartup() == false)
	{
		temp->startup();
	}
}

auto Object::remove() -> std::unique_ptr<Object>
{
	if(this->pimpl->parent == nullptr)
	{
		return nullptr;
	}

	auto [beg, end] = std::ranges::remove_if(this->pimpl->parent->pimpl->children, [this](auto&& x) { return x.get() == this; });

	if(beg == end)
	{
		return nullptr;
	}

	auto node = std::move(*beg);
	this->pimpl->parent->pimpl->children.erase(beg, end);
	node->pimpl->parent = nullptr;

	return node;
}

auto Object::getChildren() const -> const std::vector<std::unique_ptr<Object>>&
{
	return this->pimpl->children;
}

auto Object::startup() -> void
{
	if(this->pimpl->isStartup == true)
	{
		return;
	}

	for(auto& child : this->pimpl->children)
	{
		child->startup();
	}

	this->onStartup();

	this->pimpl->isStartup = true;
}

auto Object::isStartup() -> bool
{
	return this->pimpl->isStartup;
}

auto Object::onStartup() -> void
{
}
