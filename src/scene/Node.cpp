#include <aspire/scene/Node.h>

#include <aspire/core/PimplImpl.h>

using aspire::scene::Node;

struct Node::Impl
{
	std::vector<Node*> childNodes;

	int x{};
	int y{};
	int width{};
	int height{};
};

Node::Node()
{
	this->onChildAdded(
		[this](auto* x)
		{
			auto* node = dynamic_cast<Node*>(x);

			if(node == nullptr)
			{
				return;
			}

			this->pimpl->childNodes.emplace_back(node);
		});

	this->onChildRemoved([this](auto* x) { std::erase(this->pimpl->childNodes, x); });
}

Node::~Node() = default;

auto Node::setX(int x) noexcept -> void
{
	this->pimpl->x = x;
}

auto Node::getX() const noexcept -> int
{
	return this->pimpl->x;
}

auto Node::setY(int x) noexcept -> void
{
	this->pimpl->y = x;
}

auto Node::getY() const noexcept -> int
{
	return this->pimpl->y;
}

auto Node::setHeight(int x) noexcept -> void
{
	this->pimpl->height = x;
}

auto Node::getHeight() const noexcept -> int
{
	return this->pimpl->height;
}

auto Node::setWidth(int x) noexcept -> void
{
	this->pimpl->width = x;
}

auto Node::getWidth() const noexcept -> int
{
	return this->pimpl->width;
}

auto Node::childNodes() const noexcept -> std::vector<Node*>
{
	return this->pimpl->childNodes;
}
