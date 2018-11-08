#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main()
{
    char *result;    

    void *handle = dlopen("libcat_c.so", RTLD_LAZY);
    
    if(!handle)
    {
        printf("open lib error\n");
        cout<<dlerror()<<endl;
        return -1;
    }
    
    typedef char* (*cat_t)(char *buf, const char* a, const char* b);
    cat_t cat = (cat_t) dlsym(handle, "cat");
    if(!cat)
    {
        cout<<dlerror()<<endl;
        dlclose(handle);
        return -1;
    }
    
    
    char *buf = (char *)calloc(100, sizeof(char));
    result = cat(buf, "hello", "world");
    printf("result = %s\n",result);
    dlclose(handle);
    free(buf);
    return 0;
}
