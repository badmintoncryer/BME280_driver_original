#include "bme280.h"

bme280_config_t *config_table;

int8_t bme280_init(bme280_config_t *bme280_config)
{
    /* Todo */
    config_table = bme280_config;
}

int8_t bme280_exit()
{
    /* Do nothing */
}

int8_t bme280_measure(bme280_measure_date_t *measure_data)
{
    int8_t status;
    uint8_t write_data;
    uint8_t is_measuring;
    uint8_t temp_measure_data[3];

    write_data = config_table->oversamp_rate_hum;
    status = bme280_write_reg(0xF2, write_data);

    write_data = config_table->oversamp_rate_tem << 5 | config_table->oversamp_rate_pre << 2 | 0x01;
    if (status == BME280_SUCCESS) {
        status = bme280_write_reg(0xF4, write_data);
    } else {
        goto ERROR;
    }

    do {
        status = bme280_read_reg(0xF3, &is_measuring, 1);
        is_measuring = is_measuring >> 3;

        if (status != BME280_SUCCESS) {
            goto ERROR;
        }
    } while (is_measuring != 0);

    status = bme280_read_reg(0xF7, temp_measure_data, 3);
    measure_data->pressure = (uint32_t)temp_measure_data[0] << 12
                           | (uint32_t)temp_measure_data[1] << 4
                           | (uint32_t)temp_measure_data[2] >> 4;
    
    if (status == BME280_SUCCESS) {
        status = bme280_read_reg(0xFA, temp_measure_data, 3);
        measure_data->tempreture = (int32_t)temp_measure_data[0] << 12
                                 | (int32_t)temp_measure_data[1] << 4
                                 | (int32_t)temp_measure_data[2] >> 4;
    } else {
        goto ERROR;
    }

    if (status == BME280_SUCCESS) {
        status = bme280_read_reg(0xFD, temp_measure_data, 2);
        measure_data->humidity = (uint32_t)temp_measure_data[0] << 8
                               | (uint32_t)temp_measure_data[1];
    } else {
        goto ERROR;
    }

ERROR:
    return BME280_ERROR;
}

int8_t bme280_write_reg(uint8_t reg_addr, uint8_t data)
{
    int8_t status;
    uint8_t write_data[2];
    int8_t fd;

    write_data[0] = reg_addr;
    write_data[1] = data;

    status = i2c_open(&fd, 1, 0x76);
    status += i2c_write(&fd, write_data, 2);
    status += i2c_close(&fd);

    return status;
}

int8_t bme280_read_reg(uint8_t reg_addr, uint8_t *data, uint8_t size)
{
    int8_t status;
    int8_t fd;

    status = i2c_open(&fd, 1, 0x76);
    status += i2c_read(&fd, reg_addr, data, size);
    status += i2c_close(&fd);

    return status;
}
