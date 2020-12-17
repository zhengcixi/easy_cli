#include "cli_test.h"
#include "cli_mode.h"
#include "cli_iic.h"
#include "cli_spi.h"
#include "common.h"


/* 从键盘获取输入命令 */
void input_gets(char *inputs, int buflen)
{
    fgets(inputs, buflen, stdin);
}

/* 解析命令，得到的命令参数存放在argv中 */
int get_cmd_para(char *string, char argv[][CMD_PARA_CHARS])
{
    int flag = 0;
    int line = 0;
    int row = 0;
    int argc = 0;

    while (WHITE_SPACE (*string))
        string++;

    while ( *string != '\0') {
        if (WHITE_SPACE(*string)) {
            argv[row][line] = '\0';
            row++;
            argc++;
            line = 0;
            while (WHITE_SPACE (*string))
            string++;
            flag = 0;
            continue;
        }
        flag = 1;
        argv[row][line] = *string++;
        line++;
    }
    argv[row][line] = '\0';

    if (flag == 1)
        argc++;

    return argc;
}

void cli_test_one_mode(cli_mode_type_t mode)
{
    switch (mode) {
        case IIC_MODE:
            cli_test_iic_mode();
            break;
        case SPI_MODE:
            cli_test_spi_mode();
            break;
        case EXIT_MODE:
            printf("exit config mode.\n");
            exit(1);
        default:
            printf("Wrong cli mode!!!\n");
            return;
    }
}

void cli_test(void)
{
    char str[CMD_CHARS_LEN] = {0};
    char cmd[CMD_PARA_NUM][CMD_PARA_CHARS] = {0};
    int argc = 0;
    u8 i = 0;
    cli_mode_type_t cli_mode;

    while(1) {
        sal_memset(str, 0, sizeof(char)*CMD_CHARS_LEN);
        sal_memset(cmd, 0, sizeof(cmd)/sizeof(char));
        printf("(config)#");
        input_gets(str, CMD_CHARS_LEN);
        argc = get_cmd_para(str, cmd);
        if (argc != 1) {
            printf("choose mode:");
            for (i = 0; i < sizeof(cli_mode_list)/sizeof(cli_mode_t); i++) {
                printf("%s   ", cli_mode_list[i].mode_name);
            }
            printf("\n");
            continue;
        }
        
        for (i = 0; i < sizeof(cli_mode_list)/sizeof(cli_mode_t); i++) {
            if(0 == (strcasecmp(cmd[0], cli_mode_list[i].mode_name))) {
                cli_mode = cli_mode_list[i].mode;
                break;
            }
        }
        if (i == sizeof(cli_mode_list)/sizeof(cli_mode_t))
            continue;
        
        cli_test_one_mode(cli_mode);
    }
    
}






