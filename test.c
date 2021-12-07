#include <stdio.h>
#include "mymalloc.c"

int main()
{
    int *p=MyMalloc(10*sizeof(int));
    char *q=MyMalloc(20*sizeof(char));
    float *r=MyMalloc(20000*sizeof(float));
    MyFree(p);
    MyFree(q);
    MyFree(r);
    
    return 0;
}