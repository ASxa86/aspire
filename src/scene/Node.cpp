#include <aspire/scene/Node.h>

#include <aspire/core/PimplImpl.h>

using aspire::scene::Node;

struct Node::Impl
{
	auto insertChild(Node* p, std::size_t x, std::unique_ptr<Node> node) -> void
	{
		this->parent = p;
		this->children.emplace(std::begin(this->children) + x, std::move(node));
	}

	std::vector<std::unique_ptr<Node>> children;
	sigslot::signal<Node*, aspire::core::EnumMask<Node::Dirty>> signalDirty;
	Node* parent{nullptr};
	aspire::core::EnumMask<Node::Dirty> maskDirty{};
};

Node::Node()
{
}

Node::~Node() = default;

auto Node::parent() const noexcept -> Node*
{
	return this->pimpl->parent;
}

auto Node::insertChildAfter(Node* x, std::unique_ptr<Node> node) -> void
{
	const auto foundIt = std::ranges::find_if(this->pimpl->children, [x](auto&& child) { return child.get() == x; });

	if(foundIt == std::end(this->pimpl->children))
	{
		return;
	}

	const auto pos = std::distance(foundIt, std::begin(this->pimpl->children));
	this->pimpl->insertChild(this, pos + 1, std::move(node));
}

auto Node::insertChildBefore(Node* x, std::unique_ptr<Node> node) -> void
{
	const auto foundIt = std::ranges::find_if(this->pimpl->children, [x](auto&& child) { return child.get() == x; });

	if(foundIt == std::end(this->pimpl->children))
	{
		return;
	}

	const auto pos = std::distance(foundIt, std::begin(this->pimpl->children));
	this->pimpl->insertChild(this, pos, std::move(node));
}

auto Node::addChild(std::unique_ptr<Node> x) -> void
{
	this->pimpl->insertChild(this, std::size(this->pimpl->children), std::move(x));
}

auto Node::remove() -> void
{
	std::erase_if(this->pimpl->parent->pimpl->children, [this](auto&& node) { return node.get() == this; });
}

auto Node::dirty(aspire::core::EnumMask<Dirty> x) noexcept -> void
{
	this->pimpl->signalDirty(this, x);
}

auto Node::children() const noexcept -> const std::vector<std::unique_ptr<Node>>&
{
	return this->pimpl->children;
}

auto Node::onDirty(std::function<void(Node*, aspire::core::EnumMask<Dirty>)> x) -> sigslot::connection
{
	return this->pimpl->signalDirty.connect(std::move(x));
}
