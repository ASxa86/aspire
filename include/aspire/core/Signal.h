#pragma once

#include <aspire/core/Slot.h>
#include <functional>
#include <ranges>

namespace aspire
{
	namespace impl
	{
		class ASPIRE_CORE_EXPORT SignalBase
		{
		public:
			virtual ~SignalBase();
			auto connect(Connection* x) -> void;
			auto disconnect(Connection* x) -> void;
			auto connected(const Connection* x) const -> bool;

		protected:
			std::vector<Connection*> slots;
		};
	}

	template <typename T>
	class Signal;

	template <typename R, typename... Args>
	class Signal<R(Args...)> : public impl::SignalBase
	{
	public:
		using SlotType = Slot<R(Args...)>;

		auto emit(Args... args) -> void
		{
			// Need a way to combine the results of non-void type return arguments.
			for(auto* slot : this->slots)
			{
				(*static_cast<SlotType*>(slot))(std::forward<Args>(args)...);
			}
		}

		auto connect(SlotType::FunctionType x) -> std::unique_ptr<Connection>
		{
			std::unique_ptr<Connection> slot = std::make_unique<SlotType>(*this, std::move(x));
			this->SignalBase::connect(slot.get());
			return slot;
		}
	};
}
