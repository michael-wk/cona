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

hash_tab_status hash_tab_insert(hash_tab* ht, char* key)
{
    // getting the array index (hash function selected from init params)
    int idx;
    switch (ht->fn) 
    {
        case 0: idx = hash_tab_poly_rolling(ht, key);
    }
    if (!idx) return HT_INDEX_FAILED;

    printf("setting node value : %s\r\n", key);
    //hash_tab_chain_node* node;
    //node.value = key; 
    hash_tab_chain_node* nodeptr = malloc(sizeof(hash_tab_chain_node));
    nodeptr->value = key;
    nodeptr->next = NULL;

    hash_tab_chain_node* next = ht->array[idx];
    if (next == NULL) // case, nothing is there
    {
        ht->array[idx] = nodeptr;
        return HT_SUCCESS;
    }

    // parsing the linked list to check for duplicate keys
    while (next != NULL)
    {
        if (next->value == key) return HT_KEY_EXISTS;
        next = next->next;
    }

    nodeptr->next = ht->array[idx];
    ht->array[idx] = nodeptr;
    return HT_SUCCESS;
}


void hash_tab_remove(hash_tab* ht, char* key)
{
}

void hash_tab_print(hash_tab* ht)
{
    printf("Debugging print for indexes between 0 and %d\r\n", ht->BUCKETS);
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
    uint32_t res = 0;
    uint8_t idx = 0;
    while (*key != '\0')
    {
        res += (key++[idx] * c_pow(ht->int_const, idx));
        idx++;
    };
    res %= ht->BUCKETS; 
    key -= idx;
    printf("hased value for %s : %d\r\n", key, res);
    return res;
}
