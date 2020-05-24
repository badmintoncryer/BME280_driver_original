bme280: main.o bme280.o i2c.o
	gcc -Wall -O2 -o bme280.cgi main.o bme280.o i2c.o

main.o: main.c
	gcc -c main.c

bme280.o: bme280.c
	gcc -c bme280.c

i2c.o: i2c.c
	gcc -c i2c.c