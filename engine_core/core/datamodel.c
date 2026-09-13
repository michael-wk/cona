#include "datamodel.h"
#include "hashtab.h"
#include "error.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Removes scene from idx, shifting other scenes and updating meta data
void scene_rmv(scene** scenes, uint8_t idx);


void data_model_init(data_model* dm)
{
    hash_tab_init_params params = hash_tab_get_params(); 
   
    dm->scene_key_tab = malloc(sizeof(hash_tab));
    hash_tab_init(dm->scene_key_tab, &params);
    
    dm->scene_count = 0;
    dm->scenes = malloc(params.bucket_size * sizeof(scene*));
    
}


// scene methods
//=========================================================================================
scene* add_scene(data_model* dm, char* name)
{
    // check if scenes overflow uint8_t 
    if (dm->scene_count >= 255)
    {
        error_raise(DM_SCENE_OVERFLOW);
        return NULL;
    }

    // inserting key to ht;
    uint8_t res = hash_tab_insert(dm->scene_key_tab, name, dm->scene_count);
    if (res) 
    {
        error_raise(res);
        return NULL;
    }

    scene* sptr = malloc(sizeof(scene));
    scene_init(sptr, name);
    dm->scenes[dm->scene_count++] = sptr;
    printf("scene added : %s\r\n", sptr->name);

    return sptr;
}


scene* get_scene(data_model* dm, char* name)
{

}

error_status remove_scene(data_model* dm, char* name)
{
    return SUCCESS;
}

void data_model_print(data_model* dm)
{
    printf("datamodel:\r\n");
    // printing scenes:
    uint8_t idx = 0;
    while(idx < dm->scene_count)
    {
        printf("scene - idx:%d, name:%s\r\n",idx,dm->scenes[idx]->name);
        idx++;
    }
}
