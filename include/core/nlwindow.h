#ifndef _NLWINDOW_H
#define _NLWINDOW_H

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

typedef struct NLWindow
{
    GLFWwindow *window;
    int width;
    int height;
    const char *title;
} NLWindow;

/*!
*/
NLWindow *nl_create_window(int width, int height, const char *title);

/*!
*/
void nl_destroy_window(NLWindow *window);

#endif // _NLWINDOW_H
