#include <aspire/State.h>

using aspire::State;

namespace
{
	constexpr std::string_view ShaderVertex{R"(
		#version 330 core
		layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
		layout (location = 1) in vec4 aColor;
		layout (location = 2) in vec2 aTexCoord;
  
		out vec4 vertexColor; // specify a color output to the fragment shader

		void main()
		{
			gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
			vertexColor = aColor; // set the output variable to a dark-red color
		}
	)"};

	constexpr std::string_view ShaderFragment{R"(
		#version 330 core
		out vec4 FragColor;
  
		in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

		void main()
		{
			FragColor = vertexColor;
		}
	)"};
}

State::State()
{
	auto vertex = this->programDefault.addShader<Shader::Type::Vertex>();
	vertex->loadFromMemory(ShaderVertex);

	auto fragment = this->programDefault.addShader<Shader::Type::Fragment>();
	fragment->loadFromMemory(ShaderFragment);

	this->programDefault.linkShaders();

	this->programs.push(&this->programDefault);
}

auto State::pushProgram(aspire::Program* x) -> void
{
	this->programs.push(x);
}

auto State::popProgram() -> void
{
	this->programs.pop();
}

auto State::currentProgram() const -> aspire::Program*
{
	return this->programs.top();
}
