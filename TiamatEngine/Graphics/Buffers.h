#pragma once

#include <glew.h>
#include <glfw3.h>

namespace TMT 
{
	class VAO
	{
	public:
		VAO();
		~VAO();

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_ID;
	};

	class VBO
	{
	public:
		VBO();
		~VBO();

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_ID;
	};

	class IBO
	{
	public:
		IBO();
		~IBO();

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_ID;
	};
}