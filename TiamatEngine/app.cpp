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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {

    // Setup
    glfwInit();

    // Base window color
    Vector3 base_window_color(0, 0, 0);

    // The window, with size, title, and color
    TMT::Window tmt_window(800, 800, "[Tiamat Engine]", base_window_color);

    glewInit();

    glDisable(GL_DEPTH_TEST);

    // Flips stbi images on load
    stbi_set_flip_vertically_on_load(true);

    // Enables transparency
    tmt_window.enable_alpha();

    // An image, you can write to it or load your own ppm image using the Load function
    Image test_image("noise.ppm", Vector2(128, 128));

    test_image.Load("raytraced.ppm");

    //This generates an image that is black and white noise using the WritePixel function
    for (int i = 0; i < test_image.Size(); i++) 
    {
        test_image.WritePixel(rand_bw());
    }

    // Our scene, holds all scene data, the first parameter is the name, and the second parameter is the directory the scene gets saved to
    TMT::Scene scene_test("Scene A", "Scenes");

    // Our shader, this allows us to change the pixels on the screen how we'd like
    TMT::Shader* tmt_shader_basic = new TMT::Shader("Shaders/vertex_basic.glsl", "Shaders/fragment_basic_fade.glsl");

    // Our texture, the load function within the texture struct allows us to load a ppm image (the Image class type) into the texture
    TMT::Texture* test_texture = new TMT::Texture();
    // Here we load the "test_image" image
    //test_texture->load_stbi("Images/BWIcon.png");
    test_texture->load_ppm(&test_image);

    Vector3 test_color(1, 1, 1);

    float logo_fall = .05f;

    TMT::Object* test_object = new TMT::Object("Test Object", "model_transform", TMT::tmt_transform(glm::vec2(0, logo_fall), glm::vec2(1, 1), 0));
    TMT::Camera* test_camera = new TMT::Camera("Test Camera", tmt_window, TMT::tmt_transform(glm::vec2(0.f, 0.f), glm::vec2(1, 1), 0));

    scene_test.add_shader("Tiamat Basic Shader", tmt_shader_basic);
    scene_test.add_texture("Test Texture", test_texture);
    scene_test.add_material("Test Material", "Tiamat Basic Shader", "Test Texture", test_color);

    scene_test.add_mesh_renderer(TMT::Quad(), "Test Material");
    scene_test.add_object(test_camera);
    scene_test.add_object(test_object);

    scene_test.load_scene();

    TMT::Timer logo_timer(1.f);
    TMT::Timer bg_timer(2.f);

    //app loop
    while (!glfwWindowShouldClose(tmt_window.get_window())) 
    {
        // Clears the buffer and renders the window color
        tmt_window.clear();

        glfwGetFramebufferSize(tmt_window.get_window(), &tmt_window.get_width(), &tmt_window.get_height());
        framebuffer_size_callback(tmt_window.get_window(), tmt_window.get_size().m_x, tmt_window.get_size().m_y);
    
        TMT::update_delta_time();

        tmt_window.set_color(Vector3::lerp(base_window_color, Vector3::to_xyz(Vector3(179, 184, 228)), bg_timer.get_normalized_time()));
    
        scene_test.get_shader("Tiamat Basic Shader")->set_float("fade_time", logo_timer.get_normalized_time());
        
        TMT::Object& t_obj = *scene_test.get_object("Test Object");

        if (t_obj.transform.position.y > 0 && logo_timer.get_normalized_time() > 0) 
        {
            t_obj.move(0, -logo_fall * TMT::delta_time);
        }

        if (logo_timer.get_end_status()) {
            scene_test.get_texture("Test Texture")->load_stbi("Images/MGS_SolidSnake.png");
            logo_timer.stop();
        }

        // Wanna move the logo? Alright.
        if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_A) == GLFW_PRESS) {
            t_obj.move(-1 * TMT::delta_time, 0);
        }
        else if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_D) == GLFW_PRESS) {
            t_obj.move(1 * TMT::delta_time, 0);
        }

        if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_P) == GLFW_PRESS) {
            std::cout << "Window size: " << tmt_window.get_size().m_x << ", " << tmt_window.get_size().m_y << std::endl;
        }
        
        scene_test.update();
    
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

    // To insure that this is the texture that gets saved
    scene_test.get_texture("Test Texture")->load_stbi("Images/BWIcon.png");

    scene_test.export_scene();
    //tmt_shader_basic.unuse();
    //vao.unbind();

	return 0;
}