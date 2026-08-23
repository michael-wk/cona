#include "cona_math.h"

double c_pow(int x, int n)
{
    if (n == 0) return 1;
    double t = x;
    while (n-- > 1)
    {
        t *= x;
    }
    return t;
}

