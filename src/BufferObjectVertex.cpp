#include <aspire/BufferObjectVertex.h>

using aspire::BufferObjectVertex;

BufferObjectVertex::BufferObjectVertex()
{
	glGenBuffers(1, &this->handle);
}

BufferObjectVertex::~BufferObjectVertex()
{
	glDeleteBuffers(1, &this->handle);
}

auto BufferObjectVertex::bind() const -> void
{
	glBindBuffer(GL_ARRAY_BUFFER, this->handle);
}

auto BufferObjectVertex::unbind() const -> void
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto BufferObjectVertex::setVertices(std::vector<aspire::Vertex> x) -> void
{
	this->vertices = std::move(x);

	this->bind();
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(aspire::Vertex), this->vertices.data(), static_cast<GLenum>(this->getUsage()));
}

auto BufferObjectVertex::getVertices() const -> const std::vector<aspire::Vertex>&
{
	return this->vertices;
}
