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


    hash_tab* node_lookup_tab; 


} data_model;

// scene functions
//=======================================================================================

// initializes data model
void data_model_init(data_model* dm);

// scene functions
//=======================================================================================
// adds scene with given key to datamodel, returning scene
scene* add_scene(data_model* dm, char* name);

/* fetches scene with given key from datamodel.
 * Returns NULL if no scene exists with name
*/
scene* get_scene(data_model* dm, char* name);

// removes scene with given key from datamodel;
error_status remove_scene(data_model* dm, char* name);

// debugging - prints datamodel
void data_model_print(data_model* dm);

#endif
