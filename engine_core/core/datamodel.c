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
    // initializing scenes lookup table
    hash_tab_init_params params = hash_tab_get_params(); 
   
    dm->scene_key_tab = malloc(sizeof(hash_tab));
    hash_tab_init(dm->scene_key_tab, &params);
    
    dm->scene_count = 0;
    dm->scenes = malloc(params.bucket_size * sizeof(scene*));
    
    // initializing node loopup table
    hash_tab_init_params node_params = hash_tab_get_params();
    node_params->fn = DIRECT_CONVERSION; // direct conversion from char* to int

    dm->node_lookup_tab = malloc(sizeof(hash_tab));
    hash_tab_init(dm->node_lookup_tab, &node_params);

    // init node free idx stack
    dm->free_node_idxs = malloc(sizeof(u32_stack));
    u32_stack_init(dm->free_node_idxs, dm->node_lookup_tab->BUCKETS);
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
    printf("[dm] : scene added : %s\r\n", sptr->name);

    return sptr;
}


scene* get_scene(data_model* dm, char* name)
{
    // gets the metadata of the scene with passed name from dm scene key table
    // if metadata is good, gets scene at index from metadata
    uint32_t md = hash_tab_get_md(dm->scene_key_tab, name);
    
    error_status err = error_throw(_ht_get_md_succ(md), "Couldn't get MD - get_scene"); 
    if (err) return NULL;

    // the scene's index should be the metadata 
    uint8_t scene_idx = md & (0xF);
    printf("[dm] : got scene idx: %d\r\n", scene_idx);

    return dm->scenes[scene_idx];
    //return NULL;
}

error_status remove_scene(data_model* dm, char* name)
{
    // CRITICALLY - remove scene will need to shift all indexes left
    // !! This also means to update all them metadata for index positions.
    // routine will be shifting left, simultaneously decrementing MD
    
    //scene* s = get_scene(dm, name);
    //if (s == NULL) return HT_KEY_NOT_FOUND;

    // get md
    uint32_t md = hash_tab_get_md(dm->scene_key_tab, name);
    error_status err = error_throw(_ht_get_md_succ(md), "Couldn't get metadata when removing scene.");
    if (err) return err;
   
    // freeing scene
    uint8_t idx = (md & 0xFF);
    scene* rmv_scene = dm->scenes[idx];
    free(rmv_scene);

    // get index, from idx, shifting elements left until scene count, 
    for (idx += 1; idx < dm->scene_count; idx++)
    {
        // shifting left
        scene* s = dm->scenes[idx];
        dm->scenes[idx - 1] = s;
        dm->scenes[idx] = NULL;

        // updating metadata
        hash_tab_set_md_idx(dm->scene_key_tab, s->name, (idx - 1));
    }
    // removing scene key and decrementing scene

    hash_tab_remove(dm->scene_key_tab, name);
    dm->scene_count--;

    return SUCCESS;
}

void data_model_print(data_model* dm)
{
    printf("__________\r\ndatamodel: [scene_count: %d]\r\n", dm->scene_count);
    // printing scenes:
    uint8_t idx = 0;
    while(idx < dm->scene_count)
    {
        printf("scene - idx:%d, name:%s\r\n",idx,dm->scenes[idx]->name);
        idx++;
    }
}
