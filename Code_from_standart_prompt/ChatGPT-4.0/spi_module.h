#ifndef SPI_MODULE_H
#define SPI_MODULE_H

#include <stdint.h>

typedef enum {
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3
} spi_mode_t;

void spi_init(uint8_t spi_port, uint32_t clock_speed, spi_mode_t mode);
int spi_transfer(uint8_t spi_port, const uint8_t* tx_data, uint8_t* rx_data, uint16_t length);

#endif // SPI_MODULE_H
