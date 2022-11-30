#pragma once

#include <aspire/BufferObjectVertex.h>
#include <aspire/Node.h>
#include <aspire/Primitive.h>

namespace aspire
{
	/// @brief This class manages a collection of primitives that represents a geometry.
	class ASPIRE_EXPORT NodeGeometry : public Node
	{
	public:
		using Node::Node;

		auto draw() -> void override;

		auto addPrimitive(std::unique_ptr<Primitive> x) -> void;

		template <PrimitiveType T, typename... Args>
		auto addPrimitive(Args&&... x) -> T*
		{
			auto primitive = std::make_unique<T>(std::forward<Args>(x)...);
			auto p = primitive.get();
			this->addPrimitive(std::move(primitive));
			return p;
		}

		auto setVertices(std::vector<aspire::Vertex> x) -> void;
		auto getVertices() const -> const std::vector<aspire::Vertex>&;

	private:
		aspire::BufferObjectVertex vbo;
		std::vector<std::unique_ptr<Primitive>> primitives;
	};
}
