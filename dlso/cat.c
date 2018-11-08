#include <string.h>
#include <stdlib.h>

char* cat(char *buf, const char *s1, const char *s2) 
{
    strcat(buf, s1);
    strcat(buf, ", ");
    strcat(buf, s2);
    return buf;
}
