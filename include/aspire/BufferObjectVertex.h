#pragma once

#include <aspire/BufferObject.h>
#include <aspire/Vertex.h>
#include <vector>

namespace aspire
{
	class ASPIRE_EXPORT BufferObjectVertex : public BufferObject
	{
	public:
		BufferObjectVertex();
		~BufferObjectVertex() override;

		auto bind() const -> void override;
		auto unbind() const -> void override;

		auto setVertices(std::vector<aspire::Vertex> x) -> void;
		auto getVertices() const -> const std::vector<aspire::Vertex>&;

	private:
		std::vector<aspire::Vertex> vertices;
		unsigned int handle{};
	};
}
