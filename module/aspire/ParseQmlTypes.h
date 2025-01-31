#pragma once

#include <aspire/FactoryQQmlComponent.h>
#include <aspire/export.hxx>
#include <filesystem>
#include <memory>
#include <vector>

namespace aspire
{
	ASPIRE_EXPORT auto ParseQmlTypes(const std::filesystem::path& x, FactoryQQmlComponent& factory) -> void;
}
