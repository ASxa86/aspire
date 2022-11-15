#pragma once

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

		template <PrimitiveType T>
		auto addPrimitive() -> T*
		{
			auto primitive = std::make_unique<T>();
			auto p = primitive.get();
			this->addPrimitive(std::move(primitive));
			return p;
		}

	private:
		std::vector<std::unique_ptr<Primitive>> primitives;
	};
}
