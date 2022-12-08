#pragma once

#include <aspire/BufferObject.h>
#include <aspire/Node.h>
#include <aspire/Primitive.h>
#include <aspire/Program.h>

namespace aspire
{
	/// @brief This class manages a collection of primitives that represents a geometry.
	class ASPIRE_EXPORT NodeGeometry : public Node
	{
	public:
		NodeGeometry(std::string_view x = {});
		~NodeGeometry() override;

		auto addPrimitive(std::unique_ptr<Primitive> x) -> void;

		template <PrimitiveType T, typename... Args>
		auto addPrimitive(Args&&... x) -> T*
		{
			auto primitive = std::make_unique<T>(std::forward<Args>(x)...);
			auto p = primitive.get();
			this->addPrimitive(std::move(primitive));
			return p;
		}

		template <typename T>
		auto addBufferObject() -> BufferObjectTemplate<T>*
		{
			auto buffer = std::make_unique<BufferObjectTemplate<T>>();
			auto b = buffer.get();
			this->addBufferObject(std::move(buffer));
			return b;
		}

		auto addBufferObject(std::unique_ptr<BufferObject> x) -> void;

	private:
		auto onUpdate() -> void;
		auto onDraw() -> void;
		std::unique_ptr<aspire::Program> program;
		std::vector<std::unique_ptr<BufferObject>> bufferObjects;
		std::vector<std::unique_ptr<Primitive>> primitives;
		unsigned int handle{};
	};
}
