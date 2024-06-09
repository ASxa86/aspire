#include <aspire/scene/Node.h>

#include <aspire/core/PimplImpl.h>

using aspire::scene::Node;

struct Node::Impl
{
	std::vector<Node*> childNodes;
	sf::Transform local;
	sf::Transform global;
	sf::Vector2f position;
	sf::Vector2f scale{1.0F, 1.0F};
	float rotation{};
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

auto Node::setPosition(sf::Vector2f x) noexcept -> void
{
	this->pimpl->position = x;
}

auto Node::getPosition() const noexcept -> sf::Vector2f
{
	return this->pimpl->position;
}

auto Node::setScale(sf::Vector2f x) noexcept -> void
{
	this->pimpl->scale = x;
}

auto Node::getScale() const noexcept -> sf::Vector2f
{
	return this->pimpl->scale;
}

auto Node::setRotation(float x) noexcept -> void
{
	this->pimpl->rotation = x;
}

auto Node::getRotation() const noexcept -> float
{
	return this->pimpl->rotation;
}

auto Node::childNodes() const noexcept -> std::vector<Node*>
{
	return this->pimpl->childNodes;
}

auto Node::getTransformLocal() const noexcept -> sf::Transform
{
	sf::Transform transform;
	transform.translate(this->pimpl->position);
	transform.rotate(this->pimpl->rotation);
	transform.scale(this->pimpl->scale);
	return transform;
}

auto Node::getTransformGlobal() const noexcept -> sf::Transform
{
	return {};
}

auto Node::draw(sf::RenderTarget& target, sf::RenderStates states) -> void
{
	states.transform.combine(this->getTransformLocal());

	this->onDraw(target, states);

	for(auto* node : this->pimpl->childNodes)
	{
		node->draw(target, states);
	}
}

auto Node::onDraw(sf::RenderTarget& /*target*/, sf::RenderStates& /*states*/) -> void
{
}