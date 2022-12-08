#pragma once

#include <aspire/Bitmask.h>
#include <glad/glad.h>
#include <aspire/export.hxx>
#include <vector>

namespace aspire
{
	class ASPIRE_EXPORT BufferObject
	{
	public:
		BufferObject();
		virtual ~BufferObject();

		enum class BitField : int
		{
			MapRead = GL_MAP_READ_BIT,
			MapWrite = GL_MAP_WRITE_BIT,
			MapPersistent = GL_MAP_PERSISTENT_BIT,
			MapCoherent = GL_MAP_COHERENT_BIT,
			Dynamic = GL_DYNAMIC_STORAGE_BIT,
			ClientStorage = GL_CLIENT_STORAGE_BIT
		};

		auto setBitField(aspire::Bitmask<BitField> x) -> void;
		auto getBitField() const -> aspire::Bitmask<BitField>;

		virtual auto getStride() const -> std::size_t = 0;
		auto getHandle() const -> unsigned int;

		auto load(void* data, size_t size) const -> void;

	private:
		unsigned int handle{};
		aspire::Bitmask<BitField> bitField{};
	};

	template <typename T>
	class BufferObjectTemplate : public BufferObject
	{
	public:
		BufferObjectTemplate()
		{
		}

		auto getStride() const -> std::size_t override
		{
			return sizeof(T);
		}

		auto setData(std::vector<T> x) -> void
		{
			this->data = std::move(x);
			this->load(this->data.data(), this->data.size() * this->getStride());
		}

		auto getData() const -> const std::vector<T>&
		{
			return this->data;
		}

	private:
		std::vector<T> data{};
	};
}
