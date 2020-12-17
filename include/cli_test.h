#ifndef __CLI_TEST_H
#define __CLI_TEST_H
#include <stdio.h>

#define CMD_PARA_NUM    10   //一条命令最大支持的命令参数个数
#define CMD_PARA_CHARS  30   //一个参数最大支持的字符个数
#define CMD_CHARS_LEN  (CMD_PARA_NUM * CMD_PARA_CHARS)  //一个命令最大支持的字符个数

#define CLI_GET_INT_PARA(STR, V)            \
    do {                                    \
        if (is_hex_string(STR) != -1) {     \
           (V) =  hex_string_to_int32(STR); \
        } else {                            \
           (V) = string_to_int32((STR));    \
        }                                   \
    } while (0)

#define WHITE_SPACE(C)     ((C) == ' ' || (C) == '\t' || (C) == '\n')


void cli_test(void);
void input_gets(char *inputs, int buflen);
int get_cmd_para(char *string, char argv[][CMD_PARA_CHARS]);


#endif

