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

int main() {

    // Setup
    glfwInit();

    // The window, with size, title, and color
    TMT::Window tmt_window(800, 800, "[Tiamat Engine]", Vector3(0.33f, 0.41f, 0.47f));

    glewInit();

    // An image, you can write to it or load your own ppm image using the Load function
    Image test_image("noise.ppm", Vector2(128, 128));
    
    // This generates an image that is black and white noise using the WritePixel function
    for (int i = 0; i < pow(128, 2); i++) {
        test_image.WritePixel(rand_bw());
    }

    Image blurred("blurred", test_image.GetResolution());

    BoxBlur(test_image, blurred, test_image.GetResolution());

    // Our scene, holds all scene data, the first parameter is the name, and the second parameter is the directory the scene gets saved to
    TMT::Scene scene_test("Scene A", "Scenes");

    // Our shader, this allows us to change the pixels on the screen how we'd like
    TMT::Shader tmt_shader_basic = TMT::Shader("Shaders/vertex_basic.glsl", "Shaders/fragment_basic.glsl");

    // Our texture, the load function within the texture struct allows us to load a ppm image (the Image class type) into the texture
    TMT::Texture test_texture = TMT::Texture();
    // Here we load the "test_image" image
    test_texture.Load(&blurred);

    Vector3 test_color(1, 1, 1);

    scene_test.add_shader("Tiamat Basic Shader", tmt_shader_basic);
    scene_test.add_texture("Test Texture", test_texture);
    scene_test.add_material("Test Material", "Tiamat Basic Shader", "Test Texture", test_color);
    scene_test.add_mesh_renderer(TMT::Quad(), "Test Material");

    //app loop
    while (!glfwWindowShouldClose(tmt_window.get_window())) 
    {
        // Clears the buffer and renders the window color
        tmt_window.clear();

        // Renders the object
        scene_test.render();

        // Swaps the buffers and does the poll events
        tmt_window.swap_buffers();
        tmt_window.poll_events();
    }

    scene_test.export_scene();
    //tmt_shader_basic.unuse();
    //vao.unbind();

	return 0;
}