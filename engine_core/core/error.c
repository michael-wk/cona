#include "error.h"

#include <stdio.h>

void error_raise(error_status err)
{
    printf("Err! (code:%d)\r\n", err);
}


error_status error_throw(error_status err, const char* msg)
{
    if (err == 0) return err;
    printf("Err! (code:%d) - %s\r\n",err, msg);
    return err;
}
