#include "common.h"

int is_hex_string(const char *str)
{
    int loop;
    char ch;
    int len = strlen(str);

    if (*(str+0) != '0' ||  *(str+1) != 'x'  || ( len <= 2 ))
        return -1;

    for (loop = 2; loop < len; loop++) {
        ch = *(str + loop);
        if (ch >= '0' && ch <= '9')
            continue;
        if (ch >= 'A' && ch <= 'F')
            continue;
        if (ch >= 'a' && ch <= 'f')
            continue;
        
        return -1;
    }

    return 0;
}

int8_t chartoint(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch-'0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;

    printf("Warrning: Data is wrong. %x\n", ch);
    return -1;
}


int string_to_int32(char *args)
{
    int len;
    int loop;
    int value=0;

    len = strlen(args);
    for (loop = 0; loop < len; loop++) {
        if (args[loop] <= '9' && args[loop] >= '0') {
            value = value*10 + (args[loop] - '0');
        } else {
            printf("string_to_int32 error \n");
            return -1;
        }
    }
    
    return value;
}

int hex_string_to_int32(char *args)
{
    int len;
    int loop;
    int value=0;

    // the data is given by hex
    if (is_hex_string(args) != -1) {
        len = strlen(args);
        for (loop = (len>10?(len-8):2); loop < len; loop++) {
            value = (value*16 + chartoint(*(args+loop)));
        }
        return value;
    } else {
        printf( "Value \"%s\" is Invalid. You should give data via hex, start with '0x'\n", args);  
        return -1;
    }
}

int strcasecmp(const char *s1, const char *s2)
{
    u8 c1, c2;

    do {
        c1 = tolower(*s1++);
        c2 = tolower(*s2++);
    } while (c1 == c2 && c1 != 0);

    return c1 - c2;
}

void *sal_memset(void *dst_void, int32_t val, size_t len)
{
    uint8_t *dst = dst_void;

    while (len--) {
        *dst++ = (unsigned char) val;
    }

    return dst_void;
}

uint32_t sal_strtoul(const char *args, char **endptr, int32_t base)
{
   return strtoul(args, endptr, base);
}

