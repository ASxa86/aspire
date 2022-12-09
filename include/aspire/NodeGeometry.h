#pragma once

#include <aspire/BufferObject.h>
#include <aspire/Node.h>
#include <aspire/Primitive.h>
#include <aspire/Program.h>

namespace aspire
{
	/// @brief This class represents a single vertex array object and its attributes.
	class ASPIRE_EXPORT NodeGeometry : public Node
	{
	public:
		NodeGeometry(std::string_view x = {});
		~NodeGeometry() override;

		/// @brief Add a primitive to render the vertex array object as a specific primitive.
		/// @param x The primitive to render the data as.
		auto addPrimitive(std::unique_ptr<Primitive> x) -> void;

		/// @brief Create and return a pointer to a primitive defined by its PrimitiveType.
		/// @tparam ...Args Primitive type arguments that are forwarded to the primitive constructor.
		/// @tparam T The PrimitiveType to define the constructed primitive.
		/// @param ...x Primitive arguments to be forwarded during construction.
		/// @return A pointer to the constructed primitive.
		template <PrimitiveType T, typename... Args>
		auto addPrimitive(Args&&... x) -> T*
		{
			auto primitive = std::make_unique<T>(std::forward<Args>(x)...);
			auto p = primitive.get();
			this->addPrimitive(std::move(primitive));
			return p;
		}

		/// @brief Create and return a buffer object for the given type.
		/// @tparam T The buffer object type to be constructed.
		/// @return A pointer to the specific buffer object that was created.
		template <typename T>
		auto addBufferObject() -> BufferObjectTemplate<T>*
		{
			auto buffer = std::make_unique<BufferObjectTemplate<T>>();
			auto b = buffer.get();
			this->addBufferObject(std::move(buffer));
			return b;
		}

		/// @brief Add a buffer object to this geometry.
		/// @param x The buffer object to be added to this geometry.
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
