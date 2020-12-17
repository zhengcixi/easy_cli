#ifndef __COMMON_H
#define __COMMON_H
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define char_t   char
#define uint8_t  unsigned char
#define int8_t   signed char
#define uint16_t unsigned short
#define int16_t  signed short
#define uint32_t unsigned int
#define int32_t  signed int
#define uint64_t unsigned long long
#define int64_t  signed long long
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define u64 unsigned long long 


#define PHY_ERROR_PRINT(__errcode__)  printf("errcode = %d\n", __errcode__)
#define PHY_E_IF_ERROR_RETURN(op) do { \
    int32_t __rv__; \
    if ((__rv__ = (op)) < 0) { \
        PHY_ERROR_PRINT(__rv__); \
        return(__rv__); \
    } } while (0)

#define SF_ERROR_GOTO(op, ret, label) do { \
    ret = (op); \
    if (ret < 0) { \
        PHY_ERROR_PRINT(ret); \
        goto label; \
    } } while (0)

int is_hex_string(const char *str);
int8_t chartoint(char ch);
int string_to_int32(char *args);
int hex_string_to_int32(char *args);
int strcasecmp(const char *s1, const char *s2);
void *sal_memset(void *dst_void, int32_t val, size_t len);
uint32_t sal_strtoul(const char *args, char **endptr, int32_t base);


#endif 
