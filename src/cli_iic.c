#include "cli_test.h"
#include "cli_iic.h"

iic_enable_t enable_tmp;
iic_mode_t mode_tmp;

int show_iic_enable()
{
    if (enable_tmp == IIC_ENABLE)
        printf("iic  status: enable\n");
    else
        printf("iic  status: disable\n");

    return 0;
}

int show_iic_mode()
{
    if (enable_tmp == IIC_MASTER)
        printf("iic  mode: master\n");
    else
        printf("iic  mode: slave\n");

    return 0;
}

void iic_show_one_type_function( cli_cmd_iic_show_type_t iic_show_type)
{
    int phy_id = 0;
    int ret = 0;

    switch (iic_show_type) {
        case SHOW_IIC_ENABLE:
            SF_ERROR_GOTO(show_iic_enable(), ret, ERR);
            break;
        case SHOW_IIC_MODE:
            SF_ERROR_GOTO(show_iic_mode(), ret, ERR);
            break;
        default:
            goto ERR;
    }
    printf("CLI_SUCCESS.\n");
    return;
ERR:
    printf("Wrong errcode:%d\n", ret);
}


int iic_enable_set(iic_enable_t enable)
{
    enable_tmp = enable;

    return 0;
}

int iic_mode_set(iic_mode_t mode)
{
    mode_tmp = mode;

    return 0;
}


void iic_set_one_type_function(cli_cmd_iic_set_type_t cmd_iic_set_type, iic_cmd_para_t iic_cmd_para)
{
    int ret = 0;
    
    switch (cmd_iic_set_type) {
        case SET_IIC_ENABLE_STATUS:
            SF_ERROR_GOTO(iic_enable_set(iic_cmd_para.enable), ret, ERR);
            break;
        case SET_IIC_MODE_STATUS:
            SF_ERROR_GOTO(iic_mode_set(iic_cmd_para.mode), ret, ERR);
            break;
        default:
            goto ERR;
    }
    printf("CLI_SUCCESS.\n");
    return;
ERR:
    printf("execute wrong!!\n");
}


void iic_help_info(void)
{
    printf(" command       meaning  \n");
    printf("--------------------------------\n");
    printf("  exit         exit iic mode\n");
    printf("  iic          set  iic command\n");
    printf("  show         show iic command\n");
}

void iic_show_cmd_help_info(void)
{
    printf(" iic show commands list\n");
    printf("-------------------------\n");
    printf("show iic enable\n");
    printf("show iic mode\n");
}

void iic_set_cmd_help_info(void)
{
    printf(" iic set commands list\n");
    printf("------------------------\n");
    printf("iic enable|disable\n");
    printf("iic mode master|slave\n");
}

cli_cmd_iic_t cmd_iic_list[] = {
    {IIC_CMD_SET,  "iic"},
    {IIC_CMD_SHOW, "show"},
    {IIC_CMD_EXIT, "exit"},
};

void iic_set_function(char cmd[CMD_PARA_NUM][CMD_PARA_CHARS], int cmd_paras)
{
    cli_cmd_iic_set_type_t cmd_iic_set_type;
    iic_cmd_para_t iic_cmd_para;

    if (cmd_paras == 2) {
        if (strcasecmp(cmd[0], "iic") == 0) {
            if (strcasecmp(cmd[1], "enable") == 0)
                iic_cmd_para.enable = IIC_ENABLE;
            else if (strcasecmp(cmd[1], "disable") == 0)
                iic_cmd_para.enable = IIC_DISABLE;
            else
                goto ERR;
            cmd_iic_set_type = SET_IIC_ENABLE_STATUS;
        } else {
            goto ERR;
        }
    } else if (cmd_paras == 3) {
        if ((strcasecmp(cmd[0], "iic") == 0) && (strcasecmp(cmd[1], "mode") == 0)) {
            if (strcasecmp(cmd[2], "master") == 0) 
                iic_cmd_para.mode = IIC_MASTER;
            else if (strcasecmp(cmd[2], "slave") == 0) 
                iic_cmd_para.mode = IIC_SLAVE;
            else 
                goto ERR;
        } else {
            goto ERR;
        }
    } else {
        goto ERR;
    }

    iic_set_one_type_function(cmd_iic_set_type, iic_cmd_para);
    return;
ERR:
    printf("\nWrong paras!!\n");
}

void iic_show_function(char cmd[CMD_PARA_NUM][CMD_PARA_CHARS], int cmd_paras)
{
    cli_cmd_iic_show_type_t iic_show_type;
    
    if (cmd_paras == 3) {
        if ((strcasecmp(cmd[0], "show") == 0) && (strcasecmp(cmd[1], "iic") == 0)) {
            if (strcasecmp(cmd[2], "enable") == 0)
                iic_show_type = SHOW_IIC_ENABLE;
            else if (strcasecmp(cmd[2], "mode") == 0)
                iic_show_type = SHOW_IIC_MODE;
            else
                goto ERR;
        } else {
            goto ERR;
        }
    } else {
        goto ERR;
    }

    iic_show_one_type_function(iic_show_type);
    return;
ERR:
    printf("\nWrong paras!!\n");
}

void cli_test_iic_mode(void)
{
    char str[CMD_CHARS_LEN] = {0};
    char cmd[CMD_PARA_NUM][CMD_PARA_CHARS] = {0};
    int argc = 0, loop = 0;
    int iic_cmd_num = 0;
    cli_cmd_iic_type_t cmd_iic_type;

    printf("func: cli_test_iic_mode excuted!\n");
    iic_cmd_num = sizeof(cmd_iic_list)/sizeof(cli_cmd_iic_t);
    while(1) {
        sal_memset(str, 0, sizeof(char)*CMD_CHARS_LEN);
        sal_memset(cmd, 0, sizeof(cmd)/sizeof(char));
        printf("(iic-mode)#");
        input_gets(str, CMD_CHARS_LEN);
        argc = get_cmd_para(str, cmd);
        for(loop = 0; loop < iic_cmd_num; loop++){
            if(0 == (strcasecmp(cmd[0], cmd_iic_list[loop].iic_cmd_name))) {
                cmd_iic_type = cmd_iic_list[loop].iic_cmd_type;
                break;
            }
        }
        if (loop == iic_cmd_num) {
            iic_help_info();
            continue;
        }
        if (argc == 1 && (strcasecmp(cmd[0], "show") == 0 )) { 
            iic_show_cmd_help_info();
            continue;
        }
        if (argc == 1 && (strcasecmp(cmd[0], "iic") == 0 )) { 
            iic_set_cmd_help_info();
            continue;
        }

        switch (cmd_iic_type) {
            case IIC_CMD_EXIT:
                printf("exit iic mode.\n");
                return;
            case IIC_CMD_SET:
                iic_set_function(cmd, argc);
                break;
            case IIC_CMD_SHOW:
                iic_show_function(cmd, argc);
                break;
            default:
                iic_help_info();
                break;
        }
    }
    
}



