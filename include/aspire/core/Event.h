#pragma once

#include <aspire/core/Pimpl.h>
#include <aspire/core/export.hxx>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT Event
	{
	public:
		enum class Type : int
		{
			Unknown,
			Resize,
			Close
		};

		explicit Event(Type x);
		virtual ~Event();

		Event(const Event&) = delete;
		auto operator=(const Event&) -> Event& = delete;

		Event(Event&&) noexcept = delete;
		auto operator=(Event&&) -> Event& = delete;

		[[nodiscard]] auto type() const -> Type;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
