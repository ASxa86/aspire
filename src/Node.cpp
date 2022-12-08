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
	auto handled{false};
	std::visit(aspire::overloaded{// Mouse //
								  [this, &handled](EventMouse& x)
								  {
									  this->eventMouse(x);
									  handled = x.handled;
								  },
								  // Keyboard //
								  [this, &handled](EventKeyboard& x)
								  {
									  this->eventKeyboard(x);
									  handled = x.handled;
								  },
								  // Do Nothing //
								  [](auto&) {}},
			   x);

	if(handled == false)
	{
		for(auto&& child : this->children)
		{
			child->event(x);
		}
	}
}

auto Node::eventMouse(EventMouse& x) -> void
{
}

auto Node::eventKeyboard(EventKeyboard& x) -> void
{
}

auto Node::update() -> void
{
	// linkProgam

	this->signalUpdate();

	for(auto&& child : this->children)
	{
		child->update();
	}
}

auto Node::draw(aspire::State& x) -> void
{
	if(this->program != nullptr)
	{
		x.pushProgram(this->program.get());
	}

	auto p = x.currentProgram();
	p->use();

	this->signalDraw(x);

	for(auto&& child : this->children)
	{
		child->draw(x);
	}

	p->release();

	if(this->program != nullptr)
	{
		x.popProgram();
	}
}

auto Node::getOrCreateProgram() -> aspire::Program*
{
	if(this->program == nullptr)
	{
		this->program = std::make_unique<aspire::Program>();
	}

	return this->program.get();
}
