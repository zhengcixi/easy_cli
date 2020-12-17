#ifndef __CLI_IIC_H
#define __CLI_IIC_H

#include "common.h"

typedef enum iic_enable_e {
    IIC_ENABLE,
    IIC_DISABLE,
}iic_enable_t;

typedef enum iic_mode_e {
    IIC_MASTER,
    IIC_SLAVE,
}iic_mode_t;

typedef struct iic_cmd_para_e {
    iic_enable_t enable;
    iic_mode_t   mode;
}iic_cmd_para_t;


/* iic show cmd classification */
typedef enum cli_cmd_iic_show_type_e {
    SHOW_IIC_ENABLE,
    SHOW_IIC_MODE,
}cli_cmd_iic_show_type_t;

/* iic set cmd classification */
typedef enum cli_cmd_iic_set_type_e {
    SET_IIC_ENABLE_STATUS,
    SET_IIC_MODE_STATUS,
}cli_cmd_iic_set_type_t;


/* iic cmd classification */
typedef enum cli_cmd_iic_type_e {
    IIC_CMD_SET,
    IIC_CMD_SHOW,
    IIC_CMD_EXIT,
}cli_cmd_iic_type_t;

typedef struct cli_cmd_iic_s {
    cli_cmd_iic_type_t iic_cmd_type;
    char *iic_cmd_name;
}cli_cmd_iic_t;

void cli_test_iic_mode(void);


#endif

