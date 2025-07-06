#include "Buffers.h"

///VAO

//Gens the vertex arrays
TMT::VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);
}

//Deletes the vertex arrays
TMT::VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_ID);
}

//Binds the vertex arrays
void TMT::VAO::bind() const
{
	glBindVertexArray(m_ID);
}

//Unbinds the vertex arrays
void TMT::VAO::unbind() const
{
	glBindVertexArray(0);
}

/// VBO

//Gens the buffers
TMT::VBO::VBO()
{
	glGenBuffers(1, &m_ID);
}

//Deletes the buffers
TMT::VBO::~VBO()
{
	glDeleteBuffers(1, &m_ID);
}

//Binds the buffers
void TMT::VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

//Unbinds the buffers
void TMT::VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/// IBO

//Gens the buffers
TMT::IBO::IBO()
{
	glGenBuffers(1, &m_ID);
}

//Deletes the buffers
TMT::IBO::~IBO()
{
	glDeleteBuffers(1, &m_ID);
}

//Binds the buffers
void TMT::IBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

//Unbinds the buffers
void TMT::IBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
