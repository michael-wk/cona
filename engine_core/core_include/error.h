#ifndef _ERROR_
#define _ERROR_


/* Global error codes
 * Codes are split into categories
*/ 
typedef enum
{
    SUCCESS = 0,

    // hash table error codes:
    // ht error codes are delegated early on as ht metadata error status are 4 bits long
    //
    HT_INDEX_FAILED, // failed to generate a hash index
    HT_KEY_EXISTS, // key exists when attempting to insert a hash key
    HT_KEY_NOT_FOUND,

    // data model error codes:
    DM_SCENE_OVERFLOW, // data model scenes exceed the max capacity

} error_status;

/*
 * @brief Error message print corresponding to each error code
*/ 
void error_raise(error_status err); 

/*
 * @brief - throws an error of passed code, prints error message string.
*/ 
error_status error_throw(error_status err, const char* msg);

/* Calls error raise, calls function pointer callback.
 * @TODO this error handler is used for game dev not engine dev 
*/ 
// error_status error_catch(error_status err);

#endif
