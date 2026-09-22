#ifndef _HASHTAB_
#define _HASHTAB_

#include <stdint.h>
#include "error.h"

// NOTES FOR FUTURE:
// @hash_tab_insert & @hash_tab_get_md / anywhere calling hash functions:
//      -> when future hash functions are implemented, it might be more efficient to store a pointer to the hash function in the hash
//      table object rather than using switch statements, should investigate

// KNOWN FUTURE POTENTIAL REFACTORS:
// @hash_tab_insert & anywhere checking if a key exists in ht at idx
//      -> implemetning hast_bag_key_at_idx - this can replace the inline searching
//      or could not, it's the same really.


// hash table
//
// regular api functions are prefixed with hast_tab_
// secondary functions and utility functions are prefixed with _ht_
//

// defines:

#define HT_HASH_FAILED_INDEX 0xFFFFFFF0

/* =================================================================================
 * Hash table chain node
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

/* =================================================================================
 * Hash table init params
 * @brief struct containing hash table init parameters
 *  > fn            : hashing function used on hash table
 *  > bucket_size   : a number of indexes in the hash table
 *  > int_const     : constant used in hashing function
 *  > poo
*/ 
typedef struct
{
    hash_tab_hash_func fn;
    uint32_t bucket_size;
    uint32_t int_const;
} hash_tab_init_params;

// returns init params for hash table
hash_tab_init_params hash_tab_get_params(void);

/* =================================================================================
 * Hash Table
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


// Initializes hash table with passed init params.
void hash_tab_init(hash_tab* ht, hash_tab_init_params* init_params);

/* Gets hashed index of the passed key
 * selects hash function dependant on ht's hash_tab_hash_func
*/ 
uint32_t _ht_get_hashed_idx(hash_tab* ht, char* key);

/* Searches for a node of passed key at index
 * Returns hash tab chain node if found, or returns NULL if not found.
*/ 
hash_tab_chain_node* _ht_get_node_at_idx(hash_tab* ht, char* key, uint32_t idx);

/* Inserts key into hash table with passed metadata
 * Returns an error status code.
*/
error_status hash_tab_insert(hash_tab* ht, char* key, uint32_t md);

// filters hashed indexes into their corresponding error codes
// if successfully hashed, returns 0 (success).
error_status _ht_filter_idx_code(uint32_t idx);


/*
 *
*/ 
void hash_tab_remove(hash_tab* ht, char* key);


// Metadata defines:
/* Get Metadata
 * Returns the 32 bit metadata for the hash tab key
 *
 * @TODO - if I want to add some configuration to this, will need to have to add
 * options for metadata index bits to be expanded from 8 bit (255) to 15 bits
 *
 * Metadata bits:
 * > 0:7 - index in buckets -  
 *
 * Reserved bits are aligned from the left, their bits are:
 * > 31:28 success bit - corresponding to an error keycode (hash table key code)
*/ 
uint32_t hash_tab_get_md(hash_tab* ht, char* key);

// returns the error code from metmadata
error_status _ht_get_md_succ(uint32_t md);

/* sets the metadata index of for the key
 * 8 bit indexes
*/
error_status hash_tab_set_md_idx(hash_tab* ht, char* key, uint8_t idx);

// prints hash table
void hash_tab_print(hash_tab* ht);

/* ======================================================================================================
 * Hash functions:
 * - Hash functions return a uint32_t within the bounds of the buckets
 * - Max buckets for hash function are 0xFFFFFFF0 - 0xFFFFFFF1+ are reserved for error codes:
 *      - 0xFFFFFFF1 : index not hashed
*/ 

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
