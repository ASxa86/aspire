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

auto Node::event(Event& x) -> void
{
	std::visit(aspire::overloaded{// Mouse //
								  [this](EventMouse& x) { this->eventMouse(x); },
								  // Keyboard //
								  [this](EventKeyboard& x) { this->eventKeyboard(x); },
								  // Do Nothing //
								  [](auto&) {}},
			   x);
}

auto Node::eventMouse(EventMouse& x) -> void
{
	this->onEventMouse(x);

	if(x.handled == false)
	{
		for(auto&& child : this->children)
		{
			child->eventMouse(x);
		}
	}
}

auto Node::eventKeyboard(EventKeyboard& x) -> void
{
	this->onEventKeyboard(x);

	if(x.handled == false)
	{
		for(auto&& child : this->children)
		{
			child->eventKeyboard(x);
		}
	}
}

auto Node::onEventMouse(EventMouse& /*x*/) -> void
{
}

auto Node::onEventKeyboard(EventKeyboard& /*x*/) -> void
{
}
