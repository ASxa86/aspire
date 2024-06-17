#pragma once

#include <aspire/core/Event.h>
#include <aspire/core/Pimpl.h>
#include <aspire/core/export.hxx>
#include <functional>
#include <memory>
#include <sigslot/signal.hpp>
#include <string_view>
#include <vector>

namespace aspire::core
{
	class Object;

	namespace concepts
	{
		template <typename T>
		concept Object = std::is_base_of<aspire::core::Object, T>::value == true;
	}

	/// @brief This class defines the base object and how general memory manage will be handled within aspire.
	class ASPIRE_CORE_EXPORT Object
	{
	public:
		Object();
		virtual ~Object();

		Object(const Object&) = delete;
		auto operator=(const Object&) -> Object& = delete;

		Object(Object&&) noexcept = delete;
		auto operator=(Object&&) noexcept -> Object& = delete;

		/// @brief Set a name to associate with this object. Useful for identifying/debugging objects.
		/// @param x The name to assign this object.
		auto setName(std::string_view x) -> void;

		/// @brief Get the name assigned to this object.
		/// @return The name of this object.
		[[nodiscard]] auto getName() const -> std::string_view;

		/// @brief Get the owning parent of this object.
		/// @return The pointer to the owning parent. Nullptr if this object does not have a parent.
		[[nodiscard]] auto getParent() const -> Object*;

		/// @brief Add the given object to this object as a child. Claiming ownership of the child object.
		/// @param x The object to be added to this object.
		auto addChild(std::unique_ptr<Object> x) -> void;

		/// @brief Create the given object type as a child of this object and then returns the pointer to the allocated object.
		/// @tparam T The object type to create.
		/// @return The pointer to the allocated object.
		template <concepts::Object T>
		auto createChild()
		{
			auto child = std::make_unique<T>();
			auto temp = child.get();
			this->addChild(std::move(child));
			return temp;
		}

		/// @brief Remove this object from its parent.
		/// @return The pointer to this object handing ownership over to the caller.
		[[nodiscard]] auto remove() -> std::unique_ptr<Object>;

		/// @brief Get the, read-only, list of child objects.
		/// @return The list of children owned by this object.
		[[nodiscard]] auto getChildren() const -> const std::vector<std::unique_ptr<Object>>&;

		/// @brief Override to handle any event this object has received.
		/// @param x The event to be handled.
		virtual auto event(Event* x) -> void;

		/// @brief Invoke to process any overriden onStartup functions for this object and its children.
		auto startup() -> void;

		/// @brief Returns whether this object has processed its startup function.
		/// @return True if this object has been processed. Otherwise, false.
		auto isStartup() -> bool;

		auto onChildAdded(std::function<void(Object*)> x) -> sigslot::connection;
		auto onChildRemoved(std::function<void(Object*)> x) -> sigslot::connection;
		auto onStartup(std::function<void()> x) -> sigslot::connection;
		auto onFrame(std::function<void()> x) -> sigslot::connection;
		auto onFrameFixed(std::function<void()> x) -> sigslot::connection;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
