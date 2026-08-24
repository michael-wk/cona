#ifndef _SCENE_
#define _SCENE_

#include "node.h"

typedef struct
{
    char* name;
    node** children;
} scene;

// allocates and initialies scene ptr
void scene_init(scene* s, char* name);

#endif
