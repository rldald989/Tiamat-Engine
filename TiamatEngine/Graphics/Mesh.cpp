#include "Mesh.h"

TMT::Mesh::Mesh()
{
	
}

TMT::Mesh::~Mesh()
{
}

TMT::vertex* TMT::Mesh::get_vertex_data()
{
	return m_verticies.data();
}

unsigned int* TMT::Mesh::get_index_data()
{
	return m_indicies.data();
}

unsigned int TMT::Mesh::get_nr_of_verticies()
{
	return m_verticies.size();
}

unsigned int TMT::Mesh::get_nr_of_indicies()
{
	return m_indicies.size();
}

void TMT::Mesh::set(vertex* verticies, unsigned int* indicies, unsigned int nr_of_verticies, unsigned int nr_of_indicies)
{
	for (int i = 0; i < nr_of_verticies; i++)
	{
		m_verticies.push_back(verticies[i]);
	}

	for (int i = 0; i < nr_of_indicies; i++)
	{
		m_indicies.push_back(indicies[i]);
		std::cout << i << std::endl;
	}
}

TMT::Quad::Quad()
{
	vertex verticies[] =
	{
		//Top left
		Vector3(-0.5f, 0.5f, 0.0f), Vector3(0, 0, 0), Vector2(0, 1),
		//Bottom left
		Vector3(-0.5f, -0.5f, 0.0f), Vector3(0, 0, 0), Vector2(0, 0),
		//Bottom right
		Vector3(0.5f, -0.5f, 0.0f), Vector3(0, 0, 0), Vector2(1, 0),
		//Top right
		Vector3(0.5f, 0.5f, 0.0f), Vector3(0, 0, 0), Vector2(1, 1)
	};

	unsigned int nrOfVertices = sizeof(verticies) / sizeof(vertex);

	unsigned int indicies[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	unsigned int nrOfIndicies = sizeof(indicies) / sizeof(unsigned int);

	set(verticies, indicies, nrOfVertices, nrOfIndicies);

}

TMT::Quad::~Quad()
{
}
