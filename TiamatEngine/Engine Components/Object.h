#pragma once

#include "../Graphics/MeshRenderer.h"
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

	class Object
	{
	public:

		std::string matrix_name;
		tmt_transform transform;

		Object();
		Object(std::string name, const std::string& _matrix_name, const tmt_transform& _transform);
		~Object();

		virtual glm::mat4 update();
		void update_children();

		void move(float x, float y);
		void scale(float x, float y);
		void rotate(float degrees);

		void add_child(Object* child);
		Object* get_child(std::string name);
		std::map<std::string, Object*> get_children();

		glm::mat4& get_transform();

		friend class Camera;
		friend class Scene;

	protected:
		glm::mat4 m_model_transform;

		std::string m_name;
		std::map<std::string,Object*> m_child_objects;
	};
}