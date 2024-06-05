#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/scene/Node.h>
#include <aspire/widget/export.hxx>

namespace aspire::widget
{
	class ASPIRE_WIDGET_EXPORT Widget : public aspire::core::Object
	{
	public:
		Widget();
		~Widget() override;

		Widget(const Widget&) = delete;
		auto operator=(const Widget&) = delete;

		Widget(Widget&&) noexcept = delete;
		auto operator=(Widget&&) noexcept = delete;

		auto setX(int x) noexcept -> void;
		[[nodiscard]] auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		[[nodiscard]] auto getY() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		[[nodiscard]] auto getHeight() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		[[nodiscard]] auto getWidth() const noexcept -> int;

		[[nodiscard]] auto childWidgets() const noexcept -> std::vector<Widget*>;

		/// @brief This function is only save to call on the render thread and provides a way to synchronize the state of the widget with a scene
		/// node.
		/// @param x The scene node that corresponds to this widget. Nullptr if it doesn't exist.
		/// @return The root node to represent this widget in the scene.
		virtual auto update(aspire::scene::Node* x) -> std::unique_ptr<aspire::scene::Node>;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}