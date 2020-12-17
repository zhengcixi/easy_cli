#include "cli_spi.h"
#include "cli_test.h"
#include "common.h"

void spi_help_info(void)
{
    printf(" command       meaning  \n");
    printf("--------------------------------\n");
    printf("  exit         exit spi mode\n");
    printf("  spi          set  spi command\n");
    printf("  show         show spi command\n");
}

void spi_show_cmd_help_info(void)
{
    printf(" spi show commands list\n");
    printf("-------------------------\n");
    printf("show spi enable\n");
    printf("show spi mode\n");
}

void spi_set_cmd_help_info(void)
{
    printf(" spi set commands list\n");
    printf("------------------------\n");
    printf("spi enable|disable\n");
    printf("spi mode master|slave\n");
}

cli_cmd_spi_t cmd_spi_list[] = {
    {SPI_CMD_SET,  "spi"},
    {SPI_CMD_SHOW, "show"},
    {SPI_CMD_EXIT, "exit"},
};

void cli_test_spi_mode(void)
{
    char str[CMD_CHARS_LEN  ] = {0};
    char cmd[CMD_PARA_NUM][CMD_PARA_CHARS] = {0};
    int argc = 0, loop = 0;
    int spi_cmd_num = 0;
    cli_cmd_spi_type_t cmd_spi_type;

    printf("func: cli_test_spi_mode excuted!\n");
    spi_cmd_num = sizeof(cmd_spi_list)/sizeof(cli_cmd_spi_t);
    while(1) {
        sal_memset(str, 0, sizeof(char)*CMD_CHARS_LEN  );
        sal_memset(cmd, 0, sizeof(cmd)/sizeof(char));
        printf("(spi-mode)#");
        input_gets(str, CMD_CHARS_LEN  );
        argc = get_cmd_para(str, cmd);
        for(loop = 0; loop < spi_cmd_num; loop++){
            if(0 == (strcasecmp(cmd[0], cmd_spi_list[loop].spi_cmd_name))) {
                cmd_spi_type = cmd_spi_list[loop].spi_cmd_type;
                break;
            }
        }
        if (loop == spi_cmd_num) {
            spi_help_info();
            continue;
        }
        if (argc == 1 && strcasecmp(cmd[0], "show") == 0) {
            spi_show_cmd_help_info();
            continue;
        }
        if (argc == 1 && strcasecmp(cmd[0], "spi") == 0) {
            spi_set_cmd_help_info();
            continue;
        }

        switch (cmd_spi_type) {
            case SPI_CMD_EXIT:
                printf("exit spi mode.\n");
                return;
            case SPI_CMD_SET:
                break;
            case SPI_CMD_SHOW:
                break;
            default:
                spi_help_info();
                break;
        }
    }
}

