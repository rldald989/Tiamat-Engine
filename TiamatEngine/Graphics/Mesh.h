#pragma once

#include "glm.hpp"
#include "../Vector/Vector2.h"
#include "../Vector/Vector3.h"
#include <iostream>

#include <vector>

namespace TMT {

	struct vertex {
		Vector3 position;
		Vector3 color;
		Vector2 texture_coordinates;
	};

	class Mesh
	{
	public:
		Mesh();
		~Mesh();


		vertex* get_vertex_data();

		unsigned int* get_index_data();

		unsigned int get_nr_of_verticies();

		unsigned int get_nr_of_indicies();

		void set(vertex* verticies, unsigned int* indicies, unsigned int nr_of_verticies, unsigned int nr_of_indicies);

	private:
		std::vector<vertex> m_verticies;
		std::vector<unsigned int> m_indicies;

		
	};

	class Quad : public Mesh
	{
	public:
		Quad();
		~Quad();

	private:

	};

	

}