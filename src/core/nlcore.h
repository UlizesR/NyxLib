#ifndef _NLCORE_H_
#define _NLCORE_H_

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdbool.h>

typedef struct State
{
    VkInstance instance;
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

#endif // _NLCORE_H_