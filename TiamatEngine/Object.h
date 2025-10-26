#pragma once

#include "Graphics/MeshRenderer.h"
#include "Time.h"

namespace TMT {

	// transform: position, scale, rotation
	struct tmt_transform 
	{
		glm::vec2 position = glm::vec2(0);
		glm::vec2 scale = glm::vec2(1);
		float rotation = 0;

		tmt_transform(glm::vec2 pos, glm::vec2 scl, float rot) : position(pos), scale(scl), rotation(rot) {}
	};

	//struct tmt_module 
	//{
	//	virtual void update();
	//
	//};

	class Object
	{
	public:

		std::string matrix_name;
		tmt_transform transform;

		Object();
		Object(std::string _matrix_name, const tmt_transform& _transform);
		~Object();

		virtual void update();

		void move(float x, float y);
		void scale(float x, float y);
		void rotate(float degrees);

		glm::mat4 get_transform();

	private:

		glm::mat4 m_model_transform;
		//std::vector<tmt_module> m_modules;
	};
}