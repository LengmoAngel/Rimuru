/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2016-2018, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2016-04-23
 */

#include <sfud.h>
#include <stdarg.h>
#include "board_init.h"

/* send dummy data for read data */
#define DUMMY_DATA                               0xFF

static char log_buf[256u];

void sfud_log_debug(const char *file, const long line, const char *format, ...);
static void retry_delay_100us(void);

static void spi_lock(const sfud_spi *spi)
{
    __disable_irq();
}

static void spi_unlock(const sfud_spi *spi)
{
    __enable_irq();
}

/* xfer data by spi port. */
static uint8_t spi_xfer(const uint8_t value)
{
    while(0 == (SPI_GetStatus(BOARD_FLASH_SPI_PORT) & SPI_STATUS_TX_EMPTY) )
    {}
    SPI_PutData(BOARD_FLASH_SPI_PORT, value);

    while(0 == (SPI_GetStatus(BOARD_FLASH_SPI_PORT) & SPI_STATUS_RX_DONE) )
    {}
    return SPI_GetData(BOARD_FLASH_SPI_PORT);
}

/* control the cs pin output. */
static void spi_cs_control(bool enable)
{
    if (true == enable)
    {
        GPIO_ClearBits(BOARD_FLASH_CS_GPIO_PORT, BOARD_FLASH_CS_GPIO_PIN);
    }
    else
    {
        GPIO_SetBits(BOARD_FLASH_CS_GPIO_PORT, BOARD_FLASH_CS_GPIO_PIN);
    }
}

/**
 * SPI write data then read data
 */
static sfud_err spi_write_read(const sfud_spi *spi, const uint8_t *write_buf, size_t write_size, uint8_t *read_buf,
        size_t read_size) {
    sfud_err result = SFUD_SUCCESS;

    /* assert. */
    if (write_size)
    {
        SFUD_ASSERT(write_buf);
    }
    if (read_size)
    {
        SFUD_ASSERT(read_buf);
    }

    /* CS Pin valid. */
    spi_cs_control(true);

    /* put data. */
    for (uint32_t i = 0u; i < write_size; i++)
    {
        spi_xfer(write_buf[i]);
    }

    /* recv data. */
    for (uint32_t i = 0u; i < read_size; i++)
    {
        read_buf[i] = spi_xfer(DUMMY_DATA);
    }

    /* CS Pin invalid. */
    spi_cs_control(false);

    return result;
}

sfud_err sfud_spi_port_init(sfud_flash *flash)
{
    sfud_err result = SFUD_SUCCESS;

    /* Setup SPI module. */
    SPI_Master_Init_Type spi_init;
    spi_init.ClockFreqHz = BOARD_FLASH_SPI_FREQ;
    spi_init.BaudRate = BOARD_FLASH_SPI_BAUDRATE;
    spi_init.XferMode = SPI_XferMode_TxRx;
    spi_init.PolPha = SPI_PolPha_Alt2;
    spi_init.DataWidth = SPI_DataWidth_8b;
    spi_init.LSB = false;
    spi_init.AutoCS = true;
    SPI_InitMaster(BOARD_FLASH_SPI_PORT, &spi_init);

    /* Enable SPI. */
    SPI_Enable(BOARD_FLASH_SPI_PORT, true);

    /* init sfud spi obj. */
    flash->spi.wr           = spi_write_read;
    flash->spi.lock         = spi_lock;
    flash->spi.unlock       = spi_unlock;
    flash->spi.user_data    = NULL;
    flash->retry.delay      = retry_delay_100us;
    flash->retry.times      = 60u * 10000u;

    return result;
}

/**
 * This function is print debug info.
 *
 * @param file the file which has call this function
 * @param line the line number which has call this function
 * @param format output format
 * @param ... args
 */
void sfud_log_debug(const char *file, const long line, const char *format, ...)
{
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    printf("[SFUD](%s:%ld) ", file, line);
    /* must use vprintf to print */
    vsnprintf(log_buf, sizeof(log_buf), format, args);
    printf("%s\r\n", log_buf);
    va_end(args);
}

/**
 * This function is print routine info.
 *
 * @param format output format
 * @param ... args
 */
void sfud_log_info(const char *format, ...)
{
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    printf("[SFUD]");
    /* must use vprintf to print */
    vsnprintf(log_buf, sizeof(log_buf), format, args);
    printf("%s\r\n", log_buf);
    va_end(args);
}

static void retry_delay_100us(void)
{
    for (uint32_t i = 0; i < CLOCK_SYS_FREQ / 10000u; i++)
    {
        __NOP();
    }
}

/* EOF. */
