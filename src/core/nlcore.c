#include "core/nlcore.h"
#include "core/nlcore.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <stdio.h>
#include <stdbool.h>

State Core;

bool nl_init()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }
    return true;
}

void nl_shutdown()
{
    vkDestroyInstance(Core.instance, NULL);
    glfwTerminate();
}

void nlcore_vk_instance()
{
    uint32_t version;
    vkEnumerateInstanceVersion(&version);
    printf("Vulkan version: %d.%d.%d\n", VK_VERSION_MAJOR(version), VK_VERSION_MINOR(version), VK_VERSION_PATCH(version));
    // get GLFW Version
    int glfw_major, glfw_minor, glfw_revision;
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
    printf("GLFW version: %d.%d.%d\n", glfw_major, glfw_minor, glfw_revision);

    // application info
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "nlcore";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "nlcore";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;

    // extension info
    uint32_t extension_count = 0;
    const char **extensions = glfwGetRequiredInstanceExtensions(&extension_count);

    // instance info
    VkInstanceCreateInfo instance_info = {};
    instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.pApplicationInfo = &app_info;
    instance_info.enabledLayerCount = 0;
    instance_info.enabledExtensionCount = extension_count;
    instance_info.ppEnabledExtensionNames = extensions;

    if (vkCreateInstance(&instance_info, NULL, &Core.instance) != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create Vulkan instance\n");
        return;
    }
}