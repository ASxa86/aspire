#include <aspire/NodeGeometry.h>
#include <aspire/Vertex.h>
#include <glad/glad.h>

using aspire::NodeGeometry;

NodeGeometry::NodeGeometry(std::string_view x) : Node{x}
{
	this->connectUpdate([this] { this->onUpdate(); });
	this->connectDraw([this](auto&) { this->onDraw(); });

	glCreateVertexArrays(1, &this->handle);

	glEnableVertexArrayAttrib(this->handle, Vertex::Location::Position);
	glVertexArrayAttribFormat(this->handle, Vertex::Location::Position, Vertex::Size::Position, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	glVertexArrayAttribBinding(this->handle, Vertex::Location::Position, 0);

	glEnableVertexArrayAttrib(this->handle, Vertex::Location::Color);
	glVertexArrayAttribFormat(this->handle, Vertex::Location::Color, Vertex::Size::Color, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
	glVertexArrayAttribBinding(this->handle, Vertex::Location::Color, 0);

	glEnableVertexArrayAttrib(this->handle, Vertex::Location::TexCoord);
	glVertexArrayAttribFormat(this->handle, Vertex::Location::TexCoord, Vertex::Size::TexCoord, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoord));
	glVertexArrayAttribBinding(this->handle, Vertex::Location::Color, 0);
}

NodeGeometry::~NodeGeometry()
{
	if(this->handle != 0)
	{
		glDeleteVertexArrays(1, &this->handle);
	}
}

auto NodeGeometry::onUpdate() -> void
{
}

auto NodeGeometry::onDraw() -> void
{
	glBindVertexArray(this->handle);

	for(auto&& primitive : this->primitives)
	{
		primitive->draw();
	}

	glBindVertexArray(0);
}

auto NodeGeometry::addPrimitive(std::unique_ptr<Primitive> x) -> void
{
	this->primitives.emplace_back(std::move(x));
}

auto NodeGeometry::addBufferObject(std::unique_ptr<BufferObject> x) -> void
{
	glBindVertexArray(this->handle);
	glVertexArrayVertexBuffer(this->handle, 0, x->getHandle(), 0, x->getStride());
	this->bufferObjects.emplace_back(std::move(x));
}
