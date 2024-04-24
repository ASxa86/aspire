#pragma once

#include <aspire/core/export.hxx>
#include <memory>
#include <string_view>
#include <vector>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		Object(const Object&) = delete;
		auto operator=(const Object&) -> Object& = delete;

		Object(Object&&) noexcept = delete;
		auto operator=(Object&&) noexcept -> Object& = delete;

		auto setName(std::string_view x) -> void;
		[[nodiscard]] auto getName() const -> std::string_view;

	private:
		std::vector<std::unique_ptr<Object>> children;
		std::string name;
	};
}