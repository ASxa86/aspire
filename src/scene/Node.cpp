#include <aspire/scene/Node.h>

#include <aspire/core/PimplImpl.h>

using aspire::scene::Node;

struct Node::Impl
{
	std::vector<Node*> childNodes;
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

auto Node::childNodes() const noexcept -> std::vector<Node*>
{
	return this->pimpl->childNodes;
}
