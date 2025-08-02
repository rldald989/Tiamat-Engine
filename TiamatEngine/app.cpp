#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include "Graphics/Window.h"
#include "Graphics/Buffers.h"
#include "Graphics/Shader.h"

#include "Output.h"
#include "Filters.h"

#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/MeshRenderer.h"

#include "Scene.h"

#include "Timer.h"

#include "stb_image.h"

int main() {

    // Setup
    glfwInit();

    // Base window color
    Vector3 base_window_color(0, 0, 0);

    // The window, with size, title, and color
    TMT::Window tmt_window(800, 800, "[Tiamat Engine]", base_window_color);

    glewInit();

    // Flips stbi images on load
    stbi_set_flip_vertically_on_load(true);

    // Enables transparency
    tmt_window.enable_alpha();

    // An image, you can write to it or load your own ppm image using the Load function
    Image test_image("noise.ppm", Vector2(128, 128));

    test_image.Load("Images/AVYCharacter.ppm");
    
    // This generates an image that is black and white noise using the WritePixel function
    //for (int i = 0; i < pow(128, 2); i++) {
    //    test_image.WritePixel(rand_bw());
    //}

    // Our scene, holds all scene data, the first parameter is the name, and the second parameter is the directory the scene gets saved to
    TMT::Scene scene_test("Scene A", "Scenes");

    // Our shader, this allows us to change the pixels on the screen how we'd like
    TMT::Shader tmt_shader_basic = TMT::Shader("Shaders/vertex_basic.glsl", "Shaders/fragment_basic_fade.glsl");

    // Our texture, the load function within the texture struct allows us to load a ppm image (the Image class type) into the texture
    TMT::Texture test_texture = TMT::Texture();
    // Here we load the "test_image" image
    test_texture.load_stbi("Images/BWIcon.png");

    Vector3 test_color(1, 1, 1);

    scene_test.add_shader("Tiamat Basic Shader", tmt_shader_basic);
    scene_test.add_texture("Test Texture", test_texture);
    scene_test.add_material("Test Material", "Tiamat Basic Shader", "Test Texture", test_color);
    scene_test.add_mesh_renderer(TMT::Quad(), "Test Material");

    TMT::Timer logo_timer(100.f);
    TMT::Timer bg_timer(200.f);

    float last_time = 0.0f;
    float delta_time = 0.0f;

    //app loop
    while (!glfwWindowShouldClose(tmt_window.get_window())) 
    {
        // Clears the buffer and renders the window color
        tmt_window.clear();

        TMT::update_delta_time();

        tmt_window.set_color(base_window_color + ((Vector3(179, 184, 228) / 255) - base_window_color) * bg_timer.get_normalized_time());

        tmt_shader_basic.set_float("fade_time", logo_timer.get_normalized_time());

        // Renders the object
        scene_test.render();

        bg_timer.update();
        if (bg_timer.get_end_status()) {
            logo_timer.update();
        }

        // Swaps the buffers and does the poll events
        tmt_window.swap_buffers();
        tmt_window.poll_events();
    }

    std::cout << delta_time << std::endl;

    scene_test.export_scene();
    //tmt_shader_basic.unuse();
    //vao.unbind();

	return 0;
}