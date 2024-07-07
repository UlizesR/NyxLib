#include "core/nlwindow.h"

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

NLWindow *nl_create_window(int width, int height, const char *title)
{
    NLWindow *window = (NLWindow *)malloc(sizeof(NLWindow));
    window->width = width;
    window->height = height;
    window->title = title;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window->window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        free(window);
        return NULL;
    }

    return window;
}

void nl_destroy_window(NLWindow *window)
{
    glfwDestroyWindow(window->window);
    free(window);
}