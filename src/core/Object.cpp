#include <aspire/core/Kernel.h>
#include <aspire/core/Object.h>
#include <aspire/core/PimplImpl.h>
#include <algorithm>

using aspire::core::Object;

struct Object::Impl
{
	std::vector<std::unique_ptr<Object>> children;

	sigslot::signal<Object*> childRemoved;
	sigslot::signal<Object*> childAdded;
	sigslot::signal<> startup;

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

	this->pimpl->childAdded(temp);

	// Once the object has been started, we need to invoke any new objects that get added dynamically after the fact.
	if(this->isStartup() && !temp->isStartup())
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

	this->pimpl->childRemoved(node.get());

	return node;
}

auto Object::getChildren() const -> const std::vector<std::unique_ptr<Object>>&
{
	return this->pimpl->children;
}

auto Object::event(Event* /*x*/) -> void
{
}

auto Object::startup() -> void
{
	if(this->pimpl->isStartup)
	{
		return;
	}

	for(auto& child : this->pimpl->children)
	{
		child->startup();
	}

	this->pimpl->startup();

	this->pimpl->isStartup = true;
}

auto Object::isStartup() -> bool
{
	return this->pimpl->isStartup;
}

auto Object::onChildAdded(std::function<void(Object*)> x) -> sigslot::connection
{
	return this->pimpl->childAdded.connect(std::move(x));
}

auto Object::onChildRemoved(std::function<void(Object*)> x) -> sigslot::connection
{
	return this->pimpl->childRemoved.connect(std::move(x));
}

auto Object::onStartup(std::function<void()> x) -> sigslot::connection
{
	return this->pimpl->startup.connect(std::move(x));
}

auto Object::onFrame(std::function<void()> x) -> sigslot::connection
{
	return Kernel::Instance()->onFrame(std::move(x));
}

auto Object::onFrameFixed(std::function<void()> x) -> sigslot::connection
{
	return Kernel::Instance()->onFrameFixed(std::move(x));
}
