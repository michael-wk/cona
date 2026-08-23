#ifndef _HASHTAB_
#define _HASHTAB_

#include <stdint.h>

typedef enum
{
    HT_SUCCESS = 0,
    HT_INDEX_FAILED,
    HT_KEY_EXISTS

} hash_tab_status;

/* Hash table chain node
 * @brief singlely linked list node with char* value
*/ 
typedef struct htcn
{
    char* value;
    struct htcn* next;
} hash_tab_chain_node;

// Enum hash function, determins which function is used for hashing keys
typedef enum
{
    POLY_ROLLING        // 0 - polynomial rolling
} hash_tab_hash_func;

/* Hash table init params
 * @brief struct containing hash table init parameters
*/ 
typedef struct
{
    hash_tab_hash_func fn;
    uint32_t bucket_size;
    uint32_t int_const;
} hash_tab_init_params;

// returns init params for hash table
hash_tab_init_params hash_tab_get_params(void);

/* Hash Table
 * @brief hash table of strings with separate chaining collision mitigation
 * hash function is polynomial rolling
*/ 
typedef struct
{
    uint32_t BUCKETS;
    uint32_t int_const;
    hash_tab_hash_func fn;
    hash_tab_chain_node** array;
} hash_tab;


/* Initializes hash table with passed init params.
*/
void hash_tab_init(hash_tab* ht, hash_tab_init_params* init_params);

hash_tab_status hash_tab_insert(hash_tab* ht, char* key);

void hash_tab_remove(hash_tab* ht, char* key);

void hash_tab_print(hash_tab* ht);

uint32_t hash_tab_poly_rolling(hash_tab* ht, char* key);


#endif
