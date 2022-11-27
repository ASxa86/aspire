#pragma once

#include <type_traits>
#include <angle_gl.h>

namespace aspire
{
	class Primitive;

	template <typename T>
	concept PrimitiveType = std::is_base_of<Primitive, T>::value;

	class Primitive
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

		Primitive(Type x);

		auto getType() const -> Type;

		virtual auto draw() -> void = 0;

	private:
		Type type{};
	};
}
