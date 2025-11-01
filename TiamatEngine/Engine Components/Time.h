#pragma once

namespace TMT {

	extern float delta_time;
	static float last_time = 0.0f;

	static void update_delta_time() {
		float current_time = (float)glfwGetTime();
		delta_time = (current_time - last_time);
		last_time = current_time;
	}
}