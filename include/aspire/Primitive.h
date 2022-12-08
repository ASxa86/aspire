#pragma once

#include <glad/glad.h>
#include <aspire/export.hxx>
#include <type_traits>

namespace aspire
{
	class Primitive;

	/// @brief Defines a concept to enforce only template types that derive from Primitive.
	template <typename T>
	concept PrimitiveType = std::is_base_of<Primitive, T>::value;

	/// @brief This class defines a base class for managing OpenGL primitive state.
	class ASPIRE_EXPORT Primitive
	{
	public:
		enum Type : int
		{
			Points = GL_POINTS,
			Lines = GL_LINES,
			LineLoop = GL_LINE_LOOP,
			LineStrip = GL_LINE_STRIP,
			Triangles = GL_TRIANGLES,
			TriangleStrip = GL_TRIANGLE_STRIP,
			TriangleFan = GL_TRIANGLE_FAN
		};

		/// @brief Initializes the primitive with the given type.
		/// @param x The primitive type to render the bound buffer.
		Primitive(Type x);

		/// @brief Change how the bound data buffer should be rendered.
		/// @param x The primitive type to render the bound buffer.
		auto setType(Type x) -> void;

		/// @brief Get the primitive type to render the bound buffer.
		/// @return The current primitive type.
		auto getType() const -> Type;

		/// @brief Override to implement how this primitive should be rendered.
		virtual auto draw() -> void = 0;

	private:
		Type type{};
	};
}
