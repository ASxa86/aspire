#include <aspire/core/Object.h>

using aspire::Object;

Object::Object()
{
}

Object::~Object()
{
	this->destroyed.emit();
}

auto Object::setName(std::string_view x) -> void
{
	if(this->name != x)
	{
		this->name = x;
		this->nameChanged.emit(this->name);
	}
}

auto Object::getName() const -> std::string_view
{
	return this->name;
}

auto Object::addChild(std::unique_ptr<Object> x) -> void
{
	if(x == nullptr)
	{
		return;
	}

	x->parent = this;
	this->children.emplace_back(std::move(x));
	this->childAdded.emit(this->children.back().get());
}

auto Object::findChild(std::string_view x) const -> Object*
{
	auto it = std::ranges::find_if(this->children, [x](auto&& o) { return (o->getName() == x || x.empty() == true); });

	if(it == std::end(this->children))
	{
		return nullptr;
	}

	return it->get();
}

auto Object::getChildren() const -> const std::vector<std::unique_ptr<Object>>&
{
	return this->children;
}

auto Object::remove() -> std::unique_ptr<Object>
{
	if(this->parent == nullptr)
	{
		return {};
	}

	auto [first, last] = std::ranges::remove_if(this->parent->children, [this](auto&& o) { return o.get() == this; });

	if(first == std::end(this->parent->children))
	{
		return {};
	}

	// The child has been removed, its cached parents are no longer its parents. They will need to be re-cached if this object
	// get a new parent.
	this->parentCache.clear();

	std::unique_ptr<Object> o = std::move(*first);
	this->parent->children.erase(first, last);
	this->parent->childRemoved.emit(o.get());
	return o;
}

auto Object::getParent() const -> Object*
{
	return this->parent;
}

auto Object::event(aspire::Event* x) -> void
{
	switch(x->getType())
	{
		case Event::Type::Timer:
			this->eventTimer(static_cast<EventTimer*>(x));
			break;

		default:
			break;
	}
}

auto Object::initialize() -> void
{
	this->initialized.emit();

	for(auto&& child : this->children)
	{
		child->initialize();
	}
}

auto Object::terminate() -> void
{
	this->terminated.emit();

	for(auto&& child : this->children)
	{
		child->terminate();
	}
}

auto Object::track(std::unique_ptr<Connection> x) -> void
{
	this->connections.emplace_back(std::move(x));
}

auto Object::eventTimer(EventTimer*) -> void
{
}