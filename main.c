#include <GLFW/glfw3.h>
#include "core/nlcore.h"
#include "core/nlwindow.h"

#include <stdio.h>

int main(void)
{
    if (!nl_init())
    {
        fprintf(stderr, "Failed to initialize nlcore\n");
        return -1;
    }

    NLWindow *window = nl_create_window(800, 600, "Test Window");
    if (!window)
    {
        fprintf(stderr, "Failed to create window\n");
        nl_shutdown();
        return -1;
    }

    nlcore_vk_instance();
    printf("Vulkan instance created\n");

    while (!glfwWindowShouldClose(window->window))
    {
        glfwPollEvents();
        // if ESC key is pressed, close the window
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->window, GLFW_TRUE);
    }
    
    nl_destroy_window(window);
    nl_shutdown();
    return 0;
}