#include "bme280.h"

int8_t main()
{
    int8_t status;
    
    bme280_config_t config;
    bme280_measure_date_t measure_data;

    config.dev_addr = 0x76;
    config.oversamp_rate_tem = BME280_OVERSAMP_RATE_X1;
    config.oversamp_rate_pre = BME280_OVERSAMP_RATE_X1;
    config.oversamp_rate_hum = BME280_OVERSAMP_RATE_X1;

    status = bme280_init(&config);

    while(1) {
        bme280_measure(&measure_data);
        printf( "%f,", measure_data.tempreture / 100.0 );
        printf( "%f,", measure_data.pressure /100.0 );
        printf( "%f\n", measure_data.humidity / 1024.0 );

        delay_sec(1, 0);
    }

    return 0;
}
