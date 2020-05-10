#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <sys/time.h>


int8_t i2c_open(int8_t *fd, int8_t bus, uint8_t dev_addr);
int8_t i2c_close(int8_t *fd);
int8_t i2c_write(int8_t *fd, uint8_t *dat, uint8_t cnt);
int8_t i2c_read(int8_t *fd, uint8_t reg, uint8_t *dat, uint8_t cnt);
void delay_msec(uint16_t msec);
