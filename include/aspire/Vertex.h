#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace aspire
{
	/// @brief This class defines the standard vertex of aspire to be rendered by the GPU.
	struct Vertex final
	{
		/// @brief The (x, y, z) location of the vertex.
		glm::vec3 position{};

		/// @brief The (r, g, b, a) for the vertex.
		glm::vec4 color{};

		/// @brief The (u, v), normalized, coordinate for a texture mapped to this vertex.
		glm::vec2 texCoord{};

		/// @brief Defines the size of each vertex component.
		struct Size
		{
			static constexpr auto Position{sizeof(Vertex::position) / sizeof(decltype(Vertex::position)::value_type)};
			static constexpr auto Color{sizeof(Vertex::color) / sizeof(decltype(Vertex::color)::value_type)};
			static constexpr auto TexCoord{sizeof(Vertex::texCoord) / sizeof(decltype(Vertex::texCoord)::value_type)};
		};

		/// @brief Define the stride/offset of each vertex component.
		// struct Stride
		//{
		//	static constexpr auto Position{offsetof(Vertex, position)};
		//	static constexpr auto Color{offsetof(Vertex, color)};
		//	static constexpr auto TexCoord{offsetof(Vertex, texCoord)};
		// };

		/// @brief Define the shader location of each vertex component.
		struct Location
		{
			static constexpr auto Position{0};
			static constexpr auto Color{1};
			static constexpr auto TexCoord{2};
		};
	};
}
