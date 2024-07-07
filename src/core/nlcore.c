#include "nlcore.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
    vkDestroyDevice(Core.device, NULL);
    vkDestroyInstance(Core.instance, NULL);
    glfwTerminate();
}

void nlcore_vk_instance()
{
    uint32_t version;
    vkEnumerateInstanceVersion(&version);
    printf("Vulkan version: %d.%d.%d\n", VK_VERSION_MAJOR(version), VK_VERSION_MINOR(version), VK_VERSION_PATCH(version));

    int glfw_major, glfw_minor, glfw_revision;
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
    printf("GLFW version: %d.%d.%d\n", glfw_major, glfw_minor, glfw_revision);

    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "nlcore";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "nlcore";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;

    uint32_t extension_count = 0;
    const char **extensions = glfwGetRequiredInstanceExtensions(&extension_count);

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

void nlcore_vk_physical_device()
{
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(Core.instance, &device_count, NULL);
    if (device_count == 0)
    {
        fprintf(stderr, "Failed to find GPUs with Vulkan support\n");
        return;
    }

    VkPhysicalDevice devices[device_count];
    vkEnumeratePhysicalDevices(Core.instance, &device_count, devices);
    Core.physical_device = devices[0];

    VkPhysicalDeviceProperties device_properties;
    vkGetPhysicalDeviceProperties(Core.physical_device, &device_properties);
    printf("Selected GPU: %s\n", device_properties.deviceName);
}

void nlcore_vk_queue_family()
{
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(Core.physical_device, &queue_family_count, NULL);

    VkQueueFamilyProperties queue_families[queue_family_count];
    vkGetPhysicalDeviceQueueFamilyProperties(Core.physical_device, &queue_family_count, queue_families);

    for (uint32_t i = 0; i < queue_family_count; i++)
    {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            Core.graphics_queue_family_index = i;
            break;
        }
    }

    if (Core.graphics_queue_family_index == UINT32_MAX)
    {
        fprintf(stderr, "Failed to find a suitable queue family\n");
    }
}

void nlcore_vk_logical_device()
{
    float queue_priority = 1.0f;

    VkDeviceQueueCreateInfo queue_info = {};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = Core.graphics_queue_family_index;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = &queue_priority;

    VkDeviceCreateInfo device_info = {};
    device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.queueCreateInfoCount = 1;
    device_info.pQueueCreateInfos = &queue_info;
    device_info.enabledLayerCount = 0;
    device_info.ppEnabledLayerNames = NULL;
    device_info.enabledExtensionCount = 0;
    device_info.ppEnabledExtensionNames = NULL;

    if (vkCreateDevice(Core.physical_device, &device_info, NULL, &Core.device) != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create logical device\n");
        return;
    }

    vkGetDeviceQueue(Core.device, Core.graphics_queue_family_index, 0, &Core.graphics_queue);
}
