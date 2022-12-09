#pragma once

#include <aspire/Bitmask.h>
#include <glad/glad.h>
#include <aspire/export.hxx>
#include <cstddef>
#include <vector>

namespace aspire
{
	/// @brief This class manages the allocation and deltion of a general OpenGL buffer object.
	class ASPIRE_EXPORT BufferObject
	{
	public:
		BufferObject();
		virtual ~BufferObject();

		/// @brief This enumeration defines the usage for the buffer data.
		enum class BitField : int
		{
			MapRead = GL_MAP_READ_BIT,
			MapWrite = GL_MAP_WRITE_BIT,
			MapPersistent = GL_MAP_PERSISTENT_BIT,
			MapCoherent = GL_MAP_COHERENT_BIT,
			Dynamic = GL_DYNAMIC_STORAGE_BIT,
			ClientStorage = GL_CLIENT_STORAGE_BIT
		};

		/// @brief Set the bitmask that describes how the buffer data is to be utilized.
		/// @param x The bitmask of OpenGL flags for the buffer data usage.
		auto setBitField(aspire::Bitmask<BitField> x) -> void;

		/// @brief Get the bitmask that describes how the buffer data is being utilized.
		/// @return The bitmask of OpenGL flags for the buffer data usage.
		auto getBitField() const -> aspire::Bitmask<BitField>;

		/// @brief Override this function to define the stride for specific buffer data type.
		/// @return
		virtual auto getStride() const -> std::size_t = 0;

		/// @brief Get the native handle of the allocated buffer data.
		/// @return The native OpenGL handle.
		auto getHandle() const -> unsigned int;

		/// @brief Load the given data into GPU memory.
		/// @param data The pointer to an allocated block of memory.
		/// @param size The size of the given data in bytes.
		auto load(void* data, std::size_t size) const -> void;

	private:
		unsigned int handle{};
		aspire::Bitmask<BitField> bitField{};
	};

	/// @brief This class manages a specific type of buffer data defined by its parameter.
	/// @tparam T The type of the buffer data this buffer object manages.
	template <typename T>
	class BufferObjectTemplate : public BufferObject
	{
	public:
		/// @brief Overridden to define the size of the data managed by this buffer object.
		/// @return The size in bytes of the buffer data type.
		auto getStride() const -> std::size_t override
		{
			return sizeof(T);
		}

		/// @brief Set the data on this buffer object and load it into GPU memory.
		/// @param x The data to be loaded into the GPU for this buffer object.
		auto setData(std::vector<T> x) -> void
		{
			this->data = std::move(x);
			this->load(this->data.data(), this->data.size() * this->getStride());
		}

		/// @brief Get the buffer data that is loaded into GPU memory.
		/// @return The loaded buffer data.
		auto getData() const -> const std::vector<T>&
		{
			return this->data;
		}

	private:
		std::vector<T> data{};
	};
}
