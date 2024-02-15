#pragma once

#include <algorithm>
#include <aspire/export.hxx>
#include <cstdint>
#include <functional>
#include <memory>

namespace aspire
{
	namespace impl
	{
		class SignalBase;
	}

	/// @brief This class maintains common functionality between slots.
	class ASPIRE_EXPORT Connection
	{
	public:
		explicit Connection(impl::SignalBase& x);
		virtual ~Connection();

		/// @brief This enumeration describes the different errors that can occur when a slot is invoked.
		enum class Error : int
		{
			/// @brief The slot cannot be invoked due to an invalid invokable object.
			Invalid
		};

		auto disconnect() -> void;
		auto connected() const -> bool;

	private:
		impl::SignalBase* signal{};
	};

	template <typename T>
	class Slot;

	/// @brief This class wraps a std::function
	/// @tparam Return
	/// @tparam ...Args
	template <typename Return, typename... Args>
	class Slot<Return(Args...)> : public Connection
	{
	public:
		using FunctionType = std::function<Return(Args...)>;

		Slot(impl::SignalBase& s, FunctionType x) : Connection{s}, function{std::move(x)}
		{
		}

		auto operator()(Args... args) const -> void
		{
			if(this->function == nullptr)
			{
				return;
			}

			this->function(std::forward<Args>(args)...);
		}

	private:
		FunctionType function;
	};
}
