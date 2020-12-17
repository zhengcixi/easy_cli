#ifndef __CLI_MODE_H
#define __CLI_MODE_H
#include <stdio.h>

/* cli test mode */
typedef enum cli_mode_e {
    IIC_MODE,
    SPI_MODE,
    EXIT_MODE,
}cli_mode_type_t;

/* cli test mode name */
typedef struct cli_cmd_s {
    cli_mode_type_t mode;
    char *mode_name;
}cli_mode_t;

cli_mode_t cli_mode_list[] = {
    {IIC_MODE, "iic"},
    {SPI_MODE, "spi"},
    {EXIT_MODE, "exit"},
};

#endif


