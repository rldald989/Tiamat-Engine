#include "Module.h"

TMT::TMT_Module::TMT_Module(const Window& window, Object& object, std::string module_name) :
	m_window(window), m_object(object), 
	m_glfwWindow(m_window.get_window()), m_module_name(module_name)
{

}

TMT::TMT_Module::~TMT_Module()
{

}

void TMT::TMT_Module::update()
{
}