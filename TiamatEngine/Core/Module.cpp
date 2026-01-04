#include "Module.h"

TMT::TMT_Module::TMT_Module(const Window& window, Scene& scene, Object& object) : m_scene(scene), m_window(window), m_object(object), m_glfwWindow(m_window.get_window())
{

}

TMT::TMT_Module::~TMT_Module()
{

}

void TMT::TMT_Module::update()
{
}