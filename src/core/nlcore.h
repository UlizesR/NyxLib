#ifndef _NLCORE_H_
#define _NLCORE_H_

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdbool.h>

typedef struct State
{
    VkInstance instance;
    VkPhysicalDevice physical_device;
    VkDevice device;
    VkQueue graphics_queue;
    uint32_t graphics_queue_family_index;
} State;

extern State Core;

/*!
 */
bool nl_init();

/*!
 */
void nl_shutdown();

/*!
 */
void nlcore_vk_instance();

/*!
 */
void nlcore_vk_physical_device();

/*!
 */
void nlcore_vk_queue_family();

/*!
 */
void nlcore_vk_logical_device();

#endif // _NLCORE_H_
