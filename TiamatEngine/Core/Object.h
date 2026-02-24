#pragma once

#include "../Graphics/MeshRenderer.h"
#include "Time.h"
#include <optional>

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

		void move(float x, float y);
		void scale(float x, float y);
		void rotate(float degrees);

		void local_move(float x, float y);
		void local_scale(float x, float y);
		void local_rotate(float degrees);

		void set_position(float x, float y);
		void set_scale(float x, float y);

		void add_tag(std::string tag);
		bool has_tag(std::string tag);

		void parent(Object* to_child);

		glm::mat4& get_transform();

		friend class Camera;
		friend class Scene;

	protected:
		glm::mat4 m_model_transform;
		glm::mat4 m_local_transform;
		glm::mat4 m_final_transform;

		std::string m_name;
		std::unordered_map<std::string, std::string> m_tags;

		std::optional<std::string> m_parent;
	};

}