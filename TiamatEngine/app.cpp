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

#include "Core/Scene.h"
#include "Core/Timer.h"
#include "Core/Camera.h"
#include "Core/Module.h"

#include "Core/Modules/CharacterController.h"
#include "Core/Modules/SpriteAnimator.h"


#include "stb_image.h"

// Define delta time otherwise code within classes using delta_time will not work properly or at all
float TMT::delta_time = 0.0f;

float _clampf(float value, float _min, float _max) {
    return fmin(fmax(value, _min), _max);
}

int main() {
    // Setup
    glfwInit();

    // The window, with size, title, and color
    TMT::Window tmt_window(800, 800, "[Tiamat Engine]", Vector3::to_xyz(Vector3(135, 206, 235)));

    glewInit();

    // Enables transparency
    tmt_window.enable_alpha();

    // Flips stbi images on load
    stbi_set_flip_vertically_on_load(true);

    // Our scene, holds all scene data, the first parameter is the name, and the second parameter is the directory the scene gets saved to
    TMT::Scene scene_test("Scene A", "Scenes");

    // Our shader, this allows us to change the pixels on the screen how we'd like
    TMT::Shader* sprite_shader = new TMT::Shader("Shaders/vertex_basic.glsl", "Shaders/tiling_frag.glsl");
    TMT::Shader* background_shader = new TMT::Shader("Shaders/vertex_basic.glsl", "Shaders/tiling_frag.glsl");

    // Our texture, the load function within the texture struct allows us to load a ppm image (the Image class type) into the texture
    TMT::Texture* test_texture = new TMT::Texture();
    // Here we load the "test_image" image
    test_texture->load_stbi("Images/Pixel_Knight_Sheet.png", TMT::texture_filter::TMT_NEAREST);

    TMT::Texture* cotton_texture = new TMT::Texture();
    cotton_texture->load_stbi("Images/Cotton.png", TMT::texture_filter::TMT_NEAREST);

    TMT::Texture* dirt_texture = new TMT::Texture();
    dirt_texture->load_stbi("Images/Dirt.png", TMT::texture_filter::TMT_NEAREST);

    TMT::Texture* border_texture = new TMT::Texture();
    border_texture->load_stbi("Images/Border.png", TMT::texture_filter::TMT_NEAREST);

    Vector3 test_color(1, 1, 1);

    float logo_fall = .2f;

    TMT::Camera* camera = new TMT::Camera("Camera", tmt_window, TMT::tmt_transform(glm::vec2(0.f, 0.f), glm::vec2(1, 1), 0));

    TMT::Object* player_object = new TMT::Object("Player", "model_transform", TMT::tmt_transform(glm::vec2(0, logo_fall), glm::vec2(1, 1), 0));

    TMT::Object* cotton = new TMT::Object("Cotton", "model_transform", TMT::tmt_transform(glm::vec2(0), glm::vec2(1, 1), 0));

    TMT::Object* dirt = new TMT::Object("Dirt", "model_transform", TMT::tmt_transform(glm::vec2(0), glm::vec2(1, 1), 0));

    TMT::Object* border = new TMT::Object("Border", "model_transform", TMT::tmt_transform(glm::vec2(0), glm::vec2(1, 1), 0));

    scene_test.add_shader("Sprite Shader", sprite_shader);
    scene_test.add_shader("BG Shader", background_shader);

    scene_test.add_texture("Player", test_texture);
    scene_test.add_material("Player", "Sprite Shader", "Player", test_color);

    scene_test.add_texture("Cotton", cotton_texture);
    scene_test.add_material("Cotton", "BG Shader", "Cotton", test_color);

    scene_test.add_texture("Dirt", dirt_texture);
    scene_test.add_material("Dirt", "BG Shader", "Dirt", Vector3(0.647, 0.165, 0.165));

    scene_test.add_texture("Border", border_texture);
    scene_test.add_material("Border", "Sprite Shader", "Border", test_color);

    scene_test.add_mesh_renderer(TMT::Quad(), "Dirt");
    scene_test.add_mesh_renderer(TMT::Quad(), "Cotton");
    scene_test.add_mesh_renderer(TMT::Quad(), "Player");
    scene_test.add_mesh_renderer(TMT::Quad(), "Border");
    scene_test.add_object(camera, {}, true);
    scene_test.add_object(dirt, "Dirt");
    scene_test.add_object(cotton, "Cotton");
    scene_test.add_object(player_object, "Player");
    scene_test.add_object(border, "Border");
    
    // Loads the scene 
    scene_test.load_scene();

    TMT::Game::CharacterController character_controller(tmt_window, scene_test, "Player", 1.0f);
    TMT::Game::SpriteAnimator character_animator(tmt_window, scene_test, "Player", 7, 8, 10);

    TMT::Object& t_obj = *scene_test.get_object("Player");
    TMT::Object& t_cam = *scene_test.get_object("Camera");
    TMT::Object& t_cotton = *scene_test.get_object("Cotton");
    TMT::Object& t_dirt = *scene_test.get_object("Dirt");
    TMT::Object& t_border = *scene_test.get_object("Border");
    TMT::Shader& bg_shader = *scene_test.get_shader("BG Shader");
    TMT::Shader& p_shader = *scene_test.get_shader("Sprite Shader");
    float stage_length = 10;
    t_cotton.parent(&t_dirt);
    t_dirt.local_move(0.0f, -.6f);
    t_cotton.scale(stage_length, 1);
    bg_shader.set_vector2("tiling", glm::vec2(stage_length, 1));
    t_border.scale(2.f, 2.f);


    //for (int columns = 0; columns < 4; columns++) {
    //    std::cout << "[" << columns << "] : ";
    //    for (int rows = 0; rows < 4; rows++) {
    //        float value = t_cotton.get_transform()[rows][columns];
    //        std::cout << value << " ";
    //    }
    //    std::cout << "\n";
    //}

    //app loop
    while (!glfwWindowShouldClose(tmt_window.get_window())) 
    {
        // Clears the buffer and renders the window color
        tmt_window.clear();
        tmt_window.update_framebuffer();

        TMT::update_delta_time();

        character_controller.update();
        character_animator.update();

        t_border.set_position(t_obj.transform.position.x, 0.f);
        t_border.set_scale(1.f/tmt_window.get_size().m_x, 2.f);

        t_cam.set_position(-t_obj.transform.position.x, 0.0f);
        bg_shader.set_vector2("texture_position", glm::vec2(t_cotton.transform.position.x, 0));
        t_cotton.set_position(t_obj.transform.position.x, .5f);

        if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_D) == GLFW_PRESS) {
            character_animator.set_single(false);
            character_animator.select_row(1);
        }
        else if (glfwGetKey(tmt_window.get_window(), GLFW_KEY_A) == GLFW_PRESS) {
            character_animator.set_single(false);
            character_animator.select_row(0);
        }
        else  {
            character_animator.set_single(true);
            character_animator.select_row(6);
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

    scene_test.export_scene();

	return 0;
}