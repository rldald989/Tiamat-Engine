#include "Module.h"

TMT::TMT_Module::TMT_Module(const Window& window, Scene& scene) : m_scene(scene), m_window(window), m_glfwWindow(m_window.get_window())
{

}

TMT::TMT_Module::~TMT_Module()
{
}

void TMT::TMT_Module::update()
{
    TMT::Object& t_obj = *m_scene.get_object("Test Object");
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_Q) == GLFW_PRESS) {
        t_obj.local_rotate(100 * TMT::delta_time);
    }
    else if (glfwGetKey(m_glfwWindow, GLFW_KEY_E) == GLFW_PRESS) {
        t_obj.local_rotate(-100 * TMT::delta_time);
    }
}