#pragma once

#include <aspire/core/Event.h>
#include <aspire/core/Signal.h>
#include <typeindex>
#include <unordered_map>

namespace aspire
{
	class Object;

	template <typename T>
	concept ObjectType = std::is_base_of<Object, T>::value == true;

	/// @brief Object is the base class of all aspire objects. This class is designed to enable
	/// a parent child component tree architecture and communication system via signals and slots.
	class ASPIRE_EXPORT Object
	{
	public:
		Object();

		/// @brief The destroyed signal is invoked when this object is destructed.
		virtual ~Object();

		/// @brief Disable copying this object due to its polymorphic nature. Prefer to use clone instead.
		Object(const Object&) = delete;

		/// @brief Disable copying this object due to its polymorphic nature. Prefer to use clone instead.
		auto operator=(const Object&) -> Object& = delete;

		/// @brief Disable moving this object due to its polymorphic nature. Prefer to use clone instead.
		Object(Object&&) noexcept = delete;

		/// @brief Disable moving this object due to its polymorphic nature. Prefer to use clone instead.
		auto operator=(Object&&) noexcept -> Object& = delete;

		/// @brief Set a name to associate with this object.
		/// @param x The name to assign to this object.
		auto setName(std::string_view x) -> void;

		/// @brief Get the name assigned to this object.
		/// @return The name assigned to this object.
		auto getName() const -> std::string_view;

		/// @brief Add a unique child object to this object.
		/// @param x The unique child object to add.
		auto addChild(std::unique_ptr<Object> x) -> void;

		/// @brief Add a unique child object of the given type to this object.
		/// @tparam T The ObjectType to add as a child.
		/// @return The pointer to the new object.
		template <ObjectType T>
		auto addChild() -> T*
		{
			auto child = std::make_unique<T>();
			auto ptr = child.get();
			this->addChild(std::move(child));
			return ptr;
		}

		/// @brief Get the list of children owned by this object.
		/// @return A const reference list of children owned by this object.
		auto getChildren() const -> const std::vector<std::unique_ptr<Object>>&;

		/// @brief Remove this object from its parent.
		/// @return The unique_pointer that owns this object.
		auto remove() -> std::unique_ptr<Object>;

		/// @brief Get the parent of this object if it is owned by a parent.
		/// @return A pointer to the parent. Nullptr if this object has no parent.
		auto getParent() const -> Object*;

		template <typename T>
		auto getParent() -> T*
		{
			auto it = this->parentCache.find(typeid(T));

			if(it != std::end(this->parentCache))
			{
				return static_cast<T*>(it->second);
			}

			auto p = this->parent;
			auto type = dynamic_cast<T*>(p);

			while(p != nullptr && type == nullptr)
			{
				p = p->getParent();
				type = dynamic_cast<T*>(p);
			}

			this->parentCache[typeid(T)] = type;
			return type;
		}

		/// @brief Find the first child in this object's children that matches the given name.
		/// @param x The name to compare against child objects when searching.
		/// @return A pointer to the child object if it exists. Nullptr if it does not exist.
		auto findChild(std::string_view x = {}) const -> Object*;

		/// @brief Find the first child that meets the given type and name.
		/// @tparam T The object type to test against.
		/// @param x The name to test against.
		/// @return A pointer to the found child. Nullptr if it does not exist.
		template <ObjectType T>
		auto findChild(std::string_view x = {}) const -> T*
		{
			for(auto&& o : this->children)
			{
				auto* t = dynamic_cast<T*>(o.get());

				if(t != nullptr && (x.empty() == true || t->getName() == x))
				{
					return t;
				}
			}

			return nullptr;
		}

		/// @brief Find all children that meets the given type and name.
		/// @tparam T The object type to test against.
		/// @param x The name to test against.
		/// @return A vector of all children that match the given criteria.
		template <ObjectType T>
		auto findChildren(std::string_view x = {}) const -> std::vector<T*>
		{
			std::vector<T*> v;

			for(auto&& o : this->children)
			{
				auto* t = dynamic_cast<T*>(o.get());

				if(t != nullptr && (x.empty() == true || t->getName() == x))
				{
					v.emplace_back(t);
				}
			}

			return v;
		}

		auto event(aspire::Event* x) -> void;

		/// @brief Invoked once, prior to running the kernel's loop.
		auto initialize() -> void;

		/// @brief Invoked once, after exiting the kernel's loop.
		auto terminate() -> void;

		/// @brief Track the given connection keeping the signal/slot association alive until this object leaves scope.
		/// @param x The connection to track.
		auto track(std::unique_ptr<Connection> x) -> void;

		/// @brief Convenience function that handles connecting a given Object:: method to a given callable object.
		/// @tparam Signal The Object signal type.
		/// @tparam Function The callable object type.
		/// @param signal The pointer to the Object signal to connect the function to.
		/// @param f The function to be connected to the given signal.
		/// @param observer An optional Object to track the lifetime of the connection. Default 'this' object.
		template <ObjectType T, typename Signal, typename Function>
		static auto connect(T* sender, Signal signal, Object* receiver, Function f)
		{
			receiver->track((sender->*signal).connect(std::forward<Function>(f)));
		}

		/// @brief Connect to this signal to observe when this object's name changes.
		Signal<void(std::string_view)> nameChanged;

		/// @brief Connect to this signal to observe when this object has a child added.
		Signal<void(Object*)> childAdded;

		/// @brief Connect to this signal to observe when this object has a child removed.
		Signal<void(Object*)> childRemoved;

		/// @brief Connect to this signal to observe when this object is being initialized.
		Signal<void()> initialized;

		/// @brief Connect to this signal to observe when this object is being terminated.
		Signal<void()> terminated;

		/// @brief Connect to this signal to observe when this object has been destroyed.
		Signal<void()> destroyed;

	private:
		std::string name;
		std::vector<std::unique_ptr<Object>> children;
		std::vector<std::unique_ptr<Connection>> connections;
		std::unordered_map<std::type_index, Object*> parentCache;
		Object* parent{};
	};
}
