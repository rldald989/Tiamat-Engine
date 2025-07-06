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

int main() {

    // Setup
    glfwInit();

    // The window, with size, title, and color
    TMT::Window tmt_window(500, 500, "[Tiamat Engine]", Vector3(0.33f, 0.41f, 0.47f));

    glewInit();

    // An image, you can write to it or load your own ppm image using the Load function
    Image test_image("noise.ppm", Vector2(128, 128));
    
    // This generates an image that is black and white noise using the WritePixel function
    for (int i = 0; i < pow(128, 2); i++) {
        test_image.WritePixel(rand_bw());
    }

    // Our shader, this allows us to change the pixels on the screen how we'd like
    TMT::Shader tmt_shader_basic("Shaders/vertex_basic.glsl", "Shaders/fragment_basic.glsl");

    // A simple quad mesh
    TMT::Quad test_mesh;

    // Our texture, the load function within the texture struct allows us to load a ppm image (the Image class type) into the texture
    TMT::Texture test_texture;
    // Here we load the "test_image" image
    test_texture.Load(test_image);
    // Our material, it takes in our shader, our texture, and a color
    TMT::Material test_material(tmt_shader_basic, test_texture, Vector3(1, 1, 1));

    // Our mesh renderer, it takes in our mesh and our material. It manages all of the rendering, it is simple and easy to use, just call the render function in the app loop
    TMT::MeshRenderer test_renderer(test_mesh, test_material);

    //app loop
    while (!glfwWindowShouldClose(tmt_window.get_window())) 
    {
        // Clears the buffer and renders the window color
        tmt_window.clear();

        // Renders the object
        test_renderer.render();

        // Swaps the buffers and does the poll events
        tmt_window.swap_buffers();
        tmt_window.poll_events();
    }

    //tmt_shader_basic.unuse();
    //vao.unbind();

	return 0;
}