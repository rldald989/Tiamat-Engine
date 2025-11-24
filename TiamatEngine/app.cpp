#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include "Graphics/Window.h"
#include "Graphics/Buffers.h"
#include "Graphics/Shader.h"

#include "Graphics/Output.h"
#include "Graphics/Filters.h"

#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/MeshRenderer.h"

#include "Engine Components/Scene.h"
#include "Engine Components/Timer.h"
#include "Engine Components/Camera.h"

#include "stb_image.h"

// Define delta time otherwise code within classes using delta_time will not work properly or at all
float TMT::delta_time = 0.0f;

int main() {
    // Setup
    glfwInit();

    // The window, with size, title, and color
    TMT::Window tmt_window(800, 800, "[Tiamat Engine]", Vector3(0, 0, 0));

    glewInit();

    // Enables transparency
    tmt_window.enable_alpha();

    // Flips stbi images on load
    stbi_set_flip_vertically_on_load(true);

    // An image, you can write to it or load your own ppm image using the Load function
    Image test_image("noise.ppm", Vector2(128, 128));
    test_image.Init();

    //This generates an image that is black and white noise using the WritePixel function
    for (int i = 0; i < test_image.Size(); i++) 
    {
        test_image.WritePixel(rand_bw());
    }

    Image test_image_blurred = BoxBlur(test_image, test_image.GetResolution());
    test_image_blurred.Init();

    // This will export our image in the ppm format
    test_image_blurred.Export();

    // Our scene, holds all scene data, the first parameter is the name, and the second parameter is the directory the scene gets saved to
    TMT::Scene scene_test("Scene A", "Scenes");

    // Our shader, this allows us to change the pixels on the screen how we'd like
    TMT::Shader* tmt_shader_basic = new TMT::Shader("Shaders/vertex_basic.glsl", "Shaders/fragment_basic.glsl");

    // Our texture, the load function within the texture struct allows us to load a ppm image (the Image class type) into the texture
    TMT::Texture* test_texture = new TMT::Texture();
    TMT::Texture* mgs_texture = new TMT::Texture();
    // Here we load the "test_image" image
    test_texture->load_ppm(test_image_blurred);
    mgs_texture->load_stbi("Images/MGS_SolidSnake.png");

    Vector3 test_color(1, 1, 1);

    float logo_fall = .2f;

    TMT::Object* test_object = new TMT::Object("Test Object", "model_transform", TMT::tmt_transform(glm::vec2(0, logo_fall), glm::vec2(1, 1), 0));
    TMT::Object* child_object = new TMT::Object("Child Object", "model_transform", TMT::tmt_transform(glm::vec2(0, 0), glm::vec2(1, 1), 0));
    TMT::Object* three_object = new TMT::Object("Three Object", "model_transform", TMT::tmt_transform(glm::vec2(0, 0), glm::vec2(1, 1), 0));
    test_object->parent(*child_object);

    child_object->local_scale(0.5f, 0.5f);
    child_object->local_move(1.f, 0.f);
    child_object->local_rotate(45);

    child_object->parent(*three_object);
    three_object->local_scale(.5f, .5f);
    three_object->local_move(0.1f, 0.1f);
    three_object->local_rotate(45);

    TMT::Camera* test_camera = new TMT::Camera("Test Camera", tmt_window, TMT::tmt_transform(glm::vec2(0.f, 0.f), glm::vec2(1, 1), 0));


    scene_test.add_shader("Tiamat Basic Shader", tmt_shader_basic);
    scene_test.add_texture("Test Texture", test_texture);
    scene_test.add_texture("MGS", mgs_texture);
    scene_test.add_material("Test Material", "Tiamat Basic Shader", "Test Texture", test_color);
    scene_test.add_material("MGS Material", "Tiamat Basic Shader", "MGS", test_color);

    scene_test.add_mesh_renderer(TMT::Quad(), "Test Material");
    scene_test.add_mesh_renderer(TMT::Quad(), "MGS Material");
    scene_test.add_object(test_camera, true);
    scene_test.add_object(test_object, "MGS Material");
    scene_test.add_object(child_object, "Test Material");
    scene_test.add_object(three_object, "MGS Material");

    // Loads the scene 
    //scene_test.load_scene();

    TMT::Timer fall_timer(5);

    //app loop
    while (!glfwWindowShouldClose(tmt_window.get_window())) 
    {
        // Clears the buffer and renders the window color
        tmt_window.clear();
        tmt_window.update_framebuffer();

        TMT::update_delta_time();
        
        TMT::Object& t_obj = *scene_test.get_object("Test Object");

        fall_timer.update();

        if (!fall_timer.get_end_status())
        {
            t_obj.move(0, -logo_fall * TMT::delta_time);
        }

        // Wanna move the mesh? Alright.
        if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_A) == GLFW_PRESS) {
            t_obj.move(-1 * TMT::delta_time, 0);
        }
        else if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_D) == GLFW_PRESS) {
            t_obj.move(1 * TMT::delta_time, 0);
        }

        if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_Q) == GLFW_PRESS) {
            t_obj.local_rotate(100 * TMT::delta_time);
        }
        else if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_E) == GLFW_PRESS) {
            t_obj.local_rotate(-100 * TMT::delta_time);
        }

        if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_P) == GLFW_PRESS) {
            std::cout << "Window size: " << tmt_window.get_size().m_x << ", " << tmt_window.get_size().m_y << std::endl;
        }
    
        // Renders the object
        scene_test.render();
    
        // Swaps the buffers and does the poll events
        tmt_window.swap_buffers();
        tmt_window.poll_events();
    }

    // To insure that this is the texture that gets saved
    scene_test.get_texture("Test Texture")->load_ppm(test_image);

    scene_test.export_scene();

	return 0;
}