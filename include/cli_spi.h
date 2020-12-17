#ifndef __CLI_SPI_H
#define __CLI_SPI_H
#include "common.h"

/* iic cmd classification */
typedef enum cli_cmd_spi_type_e {
    SPI_CMD_SET,
    SPI_CMD_SHOW,
    SPI_CMD_EXIT,
}cli_cmd_spi_type_t;

typedef struct cli_cmd_spi_s {
    cli_cmd_spi_type_t spi_cmd_type;
    char *spi_cmd_name;
}cli_cmd_spi_t;

void cli_test_spi_mode(void);

#endif

