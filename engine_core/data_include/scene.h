#ifndef _SCENE_
#define _SCENE_

#include "node.h"

//===============================================
// Scene
//
// @note scene creation and destruction functions
// are in the datamodel header without dm / scene prefix

typedef struct
{
    char* name;
    node** children;
} scene;

// allocates and initialies scene ptr
void scene_init(scene* s, char* name);


#endif
