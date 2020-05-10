#include "i2c.h"

int8_t i2c_open(int8_t *fd, int8_t bus, uint8_t dev_addr)
{
    int8_t i2c_dev_fn[64];

    sprintf(i2c_dev_fn, "/dev/i2c-%d", bus);

    if (((*fd) = open(i2c_dev_fn, O_RDWR)) < 0) {
        return -1;
    }

    if (ioctl( (*fd), I2C_SLAVE, dev_addr ) < 0) {
        return -2;
    }

    return 0;
}

int8_t i2c_close(int8_t *fd)
{
    close(*fd);
    return 0;
}

int8_t i2c_write(int8_t *fd, uint8_t *dat, uint8_t cnt)
{
    if ((write(*fd, dat, cnt)) != cnt) {
        return -3;
    }

    return 0;
}

int8_t i2c_read(int8_t *fd, uint8_t reg, uint8_t *dat, uint8_t cnt)
{
    if ((write(*fd, &reg, 1)) != 1) {
        return -3;
    }

    if ((read(*fd, dat, cnt)) != cnt) {
        return -4;
    }

    return 0;
}

void delay_msec(uint16_t msec)
{
    struct timespec ts;

    ts.tv_sec = 0;
    ts.tv_nsec = msec * 1000 * 1000;

    nanosleep(&ts, NULL);

    return;
}
