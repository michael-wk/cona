#include "hashtab.h"
#include "cona_math.h"
#include <stdlib.h>
#include <stdio.h>

hash_tab_init_params hash_tab_get_params(void)
{
    hash_tab_init_params p;
    p.fn = POLY_ROLLING;
    p.bucket_size = 0xEF;
    p.int_const  = 0xC5;
    return p;
}


void hash_tab_init(hash_tab* ht, hash_tab_init_params* init_params)
{
    ht->BUCKETS = init_params->bucket_size;
    ht->int_const = init_params->int_const;
    ht->fn = init_params->fn; 
    ht->array = calloc(ht->BUCKETS, sizeof(void*));
}



error_status hash_tab_insert(hash_tab* ht, char* key, uint32_t md)
{

    // getting the array index (hash function selected from init params)
    uint32_t idx;
    switch (ht->fn) 
    {
        case 0: idx = hash_tab_poly_rolling(ht, key);
    }
    if (!idx) return HT_INDEX_FAILED;

    // allocating the node pointer & initializing
    hash_tab_chain_node* nodeptr = malloc(sizeof(hash_tab_chain_node));
    nodeptr->value = key;
    nodeptr->metadata = md;
    nodeptr->next = NULL;


    hash_tab_chain_node* next = ht->array[idx];
    if (next == NULL) // case, nothing is there
    {
        ht->array[idx] = nodeptr;
        return SUCCESS;
    }

    // parsing the linked list to check for duplicate keys
    while (next != NULL)
    {
        if (next->value == key) return error_throw(HT_KEY_EXISTS, "Key exist"); 
        next = next->next;
    }

    
    nodeptr->next = ht->array[idx];
    ht->array[idx] = nodeptr;
    return SUCCESS;
}


void hash_tab_remove(hash_tab* ht, char* key)
{
}


uint32_t hash_tab_get_md(hash_tab* ht, char* key)
{
    uint32_t idx;
    switch(ht->fn)
    {
        case 0: idx = hash_tab_poly_rolling(ht, key);
    }
    if (!idx)
    return 0xFFFFFFFF;
}

error_status _ht_get_md_succ(uint32_t md) 
{ 
    return (error_status)(md >> 28); 
}

void hash_tab_print(hash_tab* ht)
{
    printf("ht > debugging print for indexes between 0 and %d\r\n", ht->BUCKETS);
    for (int i = 0; i < ht->BUCKETS; i++)
    {
        printf("%d: ",i);
        hash_tab_chain_node* next = ht->array[i];
        while (next != NULL)
        {
            printf("%s ",next->value);
            next = next->next;
        }
        printf("\r\n");
    }
}


uint32_t hash_tab_poly_rolling(hash_tab* ht, char* key)
{
    unsigned int res = 0;
    uint8_t idx = 0;
    while (key[idx] != '\0')
    {
        printf("d : idx:%u , const : %u , pow : %d \r\n", idx, ht->int_const, c_pow(ht->int_const, idx));
        printf("s  char:%c, key:%u, res:%u\r\n",key[idx], key[idx], res);
        res += (key[idx] * c_pow(ht->int_const, idx));
        printf("z : res:%u\r\n", res);
        idx++;
    }

    printf("debug: %d\r\n", idx);
    res %= ht->BUCKETS; 
    printf("ht > hashed value for %s : %d\r\n", key, res);
    return (uint32_t)res;
}


//void hash_tab_set_md(hash_tab* ht, uint32_t md)
//{
//}

//void hash_tab_raise(hash_tab_status err)
//{
//    char* msg;
//    switch(err)
//    {
//        case 0: return;
//        case 1: msg = "Table index failed"; break;
//        case 2: msg = "Key already exists."; break;
//    }
//    printf("ERR! hash table : %s\r\n",msg);
//}
