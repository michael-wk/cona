#ifndef _HASHTAB_
#define _HASHTAB_

#include <stdint.h>
#include "error.h"

// NOTES FOR FUTURE:
// @hash_tab_insert & @hash_tab_get_md / anywhere calling hash functions:
//      -> when future hash functions are implemented, it might be more efficient to store a pointer to the hash function in the hash
//      table object rather than using switch statements, should investigate

// hash table
//
// regular api functions are prefixed with hast_tab_
// secondary functions and utility functions are prefixed with _ht_
//
//=====================================================================================

/* Hash table chain node
 * @brief singlely linked list node with char* value
*/ 
typedef struct htcn
{
    char* value;
    uint32_t metadata; // metadata field can be used for various purposes
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

// inserts key into hash table with passed metadata
error_status hash_tab_insert(hash_tab* ht, char* key, uint32_t md);

// removes key from hash table
void hash_tab_remove(hash_tab* ht, char* key);


/* Returns the 32 bit metadata for the hash tab key
 * 
 * Reserved bits are aligned from the left, their bits are:
 * > 31:28 success bit - corresponding to an error keycode (hash table key code)
*/ 
uint32_t hash_tab_get_md(hash_tab* ht, char* key);

error_status _ht_get_md_succ(uint32_t md); // returns get metadata success bit

// prints hash table
void hash_tab_print(hash_tab* ht);

// polynomial rolling hash function
uint32_t hash_tab_poly_rolling(hash_tab* ht, char* key);


#endif

//void hash_tab_set_md(hash_tab* ht, uint32_t md); // md will bet set per key not per h

//typedef enum7dd
//{
//    HT_SUCCESS = 0,
//    HT_INDEX_FAILED,
//    HT_KEY_EXISTS
//
//} hash_tab_status;

//void hash_tab_raise(hash_tab_status err);
