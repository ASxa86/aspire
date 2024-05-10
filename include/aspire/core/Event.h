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
			Close
		};

		explicit Event(Type x);
		virtual ~Event();

		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		Event(Event&&) noexcept = delete;
		Event& operator=(Event&&) = delete;

		[[nodiscard]] auto type() const -> Type;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
