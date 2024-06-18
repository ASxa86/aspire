#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/scene/Node.h>
#include <SFML/Graphics/Color.hpp>
#include <aspire/scene/export.hxx>

namespace aspire::scene
{
	/// @brief This class defines an application window.
	class ASPIRE_SCENE_EXPORT Window : public aspire::core::Object
	{
	public:
		static constexpr auto DefaultX{80};
		static constexpr auto DefaultY{80};
		static constexpr auto DefaultWidth{1280};
		static constexpr auto DefaultHeight{720};
		static constexpr auto DefaultTitle{"aspire"};
		inline static const sf::Color DefaultColor{static_cast<sf::Uint8>(0.2F * 255U), static_cast<sf::Uint8>(0.3F * 255U),
												   static_cast<sf::Uint8>(0.3F * 255U), static_cast<sf::Uint8>(1.0F * 255U)};

		Window();
		~Window() override;

		Window(const Window&) = delete;
		auto operator=(const Window&) = delete;

		Window(Window&&) noexcept = delete;
		auto operator=(Window&&) noexcept = delete;

		auto setX(int x) noexcept -> void;
		[[nodiscard]] auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		[[nodiscard]] auto getY() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		[[nodiscard]] auto getHeight() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		[[nodiscard]] auto getWidth() const noexcept -> int;

		auto setTitle(std::string_view x) -> void;
		[[nodiscard]] auto getTitle() const -> std::string_view;

		auto setColor(sf::Color x) noexcept -> void;
		[[nodiscard]] auto getColor() const noexcept -> sf::Color;

		auto setRootNode(std::unique_ptr<Node> x) -> void;
		[[nodiscard]] auto getRootNode() const -> Node*;

		auto event(aspire::core::Event* x) -> void override;

		auto frame() -> void;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}