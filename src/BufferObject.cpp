#include <aspire/BufferObject.h>

using aspire::BufferObject;

BufferObject::BufferObject()
{
	glCreateBuffers(1, &this->handle);
}

BufferObject::~BufferObject()
{
	if(this->handle != 0)
	{
		glDeleteBuffers(1, &this->handle);
	}
}

auto BufferObject::setBitField(aspire::Bitmask<BitField> x) -> void
{
	this->bitField = x;
}

auto BufferObject::getBitField() const -> aspire::Bitmask<BitField>
{
	return this->bitField;
}

auto BufferObject::getHandle() const -> unsigned int
{
	return this->handle;
}

auto BufferObject::load(void* data, std::size_t size) const -> void
{
	glNamedBufferStorage(this->handle, size, data, static_cast<GLbitfield>(this->bitField.get()));
}
