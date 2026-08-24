#ifndef _DATA_MODEL_
#define _DATA_MODEL_

#include "scene.h"
#include "hashtab.h"

//typedef enum // - MOVED TO ERROR.H
//{
//    DM_SUCCESS = 0, // success
//    DM_FAILED,      // generic failed
//    DM_KEY_EXISTS,
//    DM_SCENE_OVERFLOW,
//} data_model_status;


/* Data Model
 * @brief structure containing the scene trees of nodes that make up the game project
*/
typedef struct
{
    uint8_t scene_count; // 255 scenes is pretty a lot tbh;
    scene** scenes;
    hash_tab* scene_key_tab; // scene key table contains the key map of each scene

} data_model;

void data_model_init(data_model* dm);

scene* add_scene(data_model* dm, char* name);

error_status remove_scene(data_model* dm, char* name);

void data_model_print(data_model* dm);

#endif
