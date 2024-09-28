#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/scene/export.hxx>

namespace aspire::scene
{
	class ASPIRE_SCENE_EXPORT Node : public aspire::core::Object
	{
	public:
		Node();
		~Node() override;

		Node(const Node&) = delete;
		auto operator=(const Node&) = delete;

		Node(Node&&) noexcept = delete;
		auto operator=(Node&&) noexcept = delete;

		[[nodiscard]] auto childNodes() const noexcept -> std::vector<Node*>;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
