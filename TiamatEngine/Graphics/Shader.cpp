#include "Shader.h"

TMT::Shader::Shader(const char* vFile, const char* fFile)
{
	// The data for the vertex and fragment shaders
	unsigned int vertex_shader = 0;
	unsigned int fragment_shader = 0;

	// Processes the shaders (the ones that were inputed in the vFile and fFile parameters)
	vertex_shader = process_shader(GL_VERTEX_SHADER, (char*)vFile);
	fragment_shader = process_shader(GL_FRAGMENT_SHADER, (char*)fFile);

	// Links the shader
	Link(vertex_shader, fragment_shader);
}

TMT::Shader::~Shader()
{
}

void TMT::Shader::use()
{
	// Uses the shader program
	glUseProgram(m_ID);
}

void TMT::Shader::unuse()
{
	// unuses the shader program
	glUseProgram(0);
}

void TMT::Shader::delete_shader()
{
	// Deletes the shader program
	glDeleteProgram(m_ID);
}

unsigned int TMT::Shader::get_program()
{
	// Gets the shader program
	return m_ID;
}

// Sets an integer in the shader
void TMT::Shader::set_integer(const char* name, int value)
{
	use();

	glUniform1i(glGetUniformLocation(value, name), value);

	unuse();
}

// Sets an float in the shader
void TMT::Shader::set_float(const char* name, float value)
{
	use();

	glUniform1f(glGetUniformLocation(m_ID, name), value);

	unuse();
}

// Sets an Vector 2 in the shader
void TMT::Shader::set_vector2(const char* name, glm::fvec2 value)
{
	use();

	glUniform2fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));

	unuse();
}

// Sets an Vector 3 in the shader
void TMT::Shader::set_vector3(const char* name, glm::fvec3 value)
{
	use();

	glUniform3fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));

	unuse();
}

// Sets an Vector 4 in the shader
void TMT::Shader::set_vector4(const char* name, glm::fvec4 value)
{
	use();

	glUniform4fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));

	unuse();
}

// Sets an Matrix 3 in the shader
void TMT::Shader::set_matrix3(const char* name, glm::mat3 value, bool transpose)
{
	use();

	glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, transpose, glm::value_ptr(value));

	unuse();
}

// Sets an Matrix 4 in the shader
void TMT::Shader::set_matrix4(const char* name, glm::mat4 value, bool transpose)
{
	use();

	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, transpose, glm::value_ptr(value));

	unuse();
}
