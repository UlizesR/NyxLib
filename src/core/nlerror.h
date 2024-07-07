#ifndef NLERROR_H
#define NLERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <GLFW/glfw3.h>

#define EXPECT(ERROR, FORMAT, ...) {                                                                                                        \
    int macroErrorCode = ERROR;                                                                                                             \
    if(macroErrorCode) {                                                                                                                    \
        fprintf(stderr, "%s -> %s -> %i -> Error(%i):\n\t" FORMAT "\n", __FILE__, __func__, __LINE__, macroErrorCode, ##__VA_ARGS__);  \
        raise(SIGABRT);                                                                                                                     \
    }                                                                                                                                       \
}

#endif // NLERROR_H