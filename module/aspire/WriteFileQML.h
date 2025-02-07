#pragma once

#include <QObject>
#include <aspire/export.hxx>
#include <filesystem>

namespace aspire
{
	/// @brief Write the given object to a QML file.
	/// @param x The object to be written to file.
	/// @param file The fully qualified path to write the file to.
	ASPIRE_EXPORT auto WriteFileQML(QObject* x, const std::filesystem::path& file) -> void;
}