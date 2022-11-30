#pragma once

#include <angle_gl.h>
#include <aspire/export.hxx>

namespace aspire
{
	class ASPIRE_EXPORT BufferObject
	{
	public:
		virtual ~BufferObject();

		enum class Usage : int
		{
			DrawStream = GL_STREAM_DRAW,
			DrawStatic = GL_STATIC_DRAW,
			DrawDynamic = GL_DYNAMIC_DRAW
		};

		auto setUsage(Usage x) -> void;
		auto getUsage() const -> Usage;

		virtual auto bind() const -> void = 0;
		virtual auto unbind() const -> void = 0;

	private:
		Usage usage{Usage::DrawStatic};
	};
}
