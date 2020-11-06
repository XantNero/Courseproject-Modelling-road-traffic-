#include "Window.h"
#include <assert.h>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Window::Window() 
{
    WindowProps props;
    m_data.Title = props.Title;
    m_data.Height = props.Height;
    m_data.Width = props.Width;
    m_data.WindowPointer = this;

    if (!glfwInit()) {
        assert(false);  
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

    m_Window = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Title.c_str(), NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
        assert(false);
    }

     glfwMakeContextCurrent(m_Window);

    if(glewInit() != GLEW_OK) {
        assert(false);
    }   

    glfwSetWindowUserPointer(m_Window, &m_data);
    glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
    glfwSetKeyCallback(m_Window, KeyCallback);
    glfwSetCharCallback(m_Window, CharCallback);
    glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
    glfwSetScrollCallback(m_Window, ScrollCallback);
    glfwSetCursorPosCallback(m_Window, CursorPosCallback);
}

Window::Window(const WindowProps& props)
{
    m_data.Title = props.Title;
    m_data.Height = props.Height;
    m_data.Width = props.Width;
    m_data.WindowPointer = this;

    if (!glfwInit()) {
        assert(false);  
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

    m_Window = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Title.c_str(), NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
        assert(false);
    }

     glfwMakeContextCurrent(m_Window);

    if(glewInit() != GLEW_OK) {
        assert(false);
    }   

    glfwSetWindowUserPointer(m_Window, &m_data);
    glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
    glfwSetKeyCallback(m_Window, KeyCallback);
    glfwSetCharCallback(m_Window, CharCallback);
    glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
    glfwSetScrollCallback(m_Window, ScrollCallback);
    glfwSetCursorPosCallback(m_Window, CursorPosCallback);
}

Window::~Window() 
{
    glfwDestroyWindow(m_Window);
}

void Window::onUpdate() 
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void Window::setWindowSizeCallback(void (*callback)(Window* window, int width, int height)) 
{
    m_data.WindowSizeCallback = callback;
}

void Window::setKeyCallback(void (*callback)(Window* window, int key, int scancode, int action, int mods)) 
{
    m_data.KeyCallback = callback;
}

void Window::setCharCallback(void (*callback)(Window* window, unsigned int keycode)) 
{
    m_data.CharCallback = callback;
}

void Window::setMouseButtonCallback(void (*callback)(Window* window, int button, int action, int mods)) 
{
    m_data.MouseButtonCallback = callback;
}

void Window::setScrollCallback(void (*callback)(Window* window, double xOffset, double yOffset)) 
{
    m_data.ScrollCallback = callback;
}

void Window::setCursorPosCallback(void (*callback)(Window* window, double xPos, double yPos)) 
{
    m_data.CursorPosCallback = callback;
}

unsigned int Window::getWidth() const
{
    return m_data.Width;
}

unsigned int Window::getHeight() const
{
    return m_data.Height;
}

void Window::shutDown() 
{
        glfwTerminate();
}

void WindowSizeCallback(GLFWwindow* window, int width, int height) 
{
    WindowData *data = (WindowData*)glfwGetWindowUserPointer(window);
    data->Width = width;
    data->Height = height;
    if (data->WindowSizeCallback != nullptr)
        data->WindowSizeCallback(data->WindowPointer, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    WindowData *data = (WindowData*)glfwGetWindowUserPointer(window);
    if (data->KeyCallback != nullptr)
        data->KeyCallback(data->WindowPointer, key, scancode, action, mods);
}

void CharCallback(GLFWwindow* window, unsigned int keycode) 
{
    WindowData *data = (WindowData*)glfwGetWindowUserPointer(window);
    if (data->CharCallback != nullptr)
        data->CharCallback(data->WindowPointer, keycode);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
    WindowData *data = (WindowData*)glfwGetWindowUserPointer(window);
    if (data->MouseButtonCallback != nullptr)
        data->MouseButtonCallback(data->WindowPointer, button, action, mods);
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) 
{
    WindowData *data = (WindowData*)glfwGetWindowUserPointer(window);
    if (data->ScrollCallback != nullptr)
        data->ScrollCallback(data->WindowPointer, xOffset, yOffset);
}

void CursorPosCallback(GLFWwindow* window, double xPos, double yPos) 
{
    WindowData *data = (WindowData*)glfwGetWindowUserPointer(window);
    data->CursorPosX = xPos;
    data->CursorPosY = yPos;
    if (data->CursorPosCallback != nullptr)
        data->CursorPosCallback(data->WindowPointer, xPos, yPos);    
}