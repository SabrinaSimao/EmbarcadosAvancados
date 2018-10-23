TARGET = hps_gpio
PORT = 8081
ALT_DEVICE_FAMILY ?= soc_cv_av

HWLIBS_ROOT = $(SOCEDS_HWLIB)

IP = 192.168.0.102

CFLAGS = -g -Wall -Werror -I$(HWLIBS_ROOT)/include -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY) -D$(ALT_DEVICE_FAMILY)
LDFLAGS = -g -Wall -Werror

CROSS_COMPILE = $(GCC_Linaro)/arm-linux-gnueabihf-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
ARCH = arm

DIR = /work/
PATHTOTARGET = /home/sabrina/work/blinkhps/hps_gpio

.PHONY: build
build: $(TARGET)

$(TARGET): main.o
	$(LD) $(LDFLAGS)   $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

copy:
	scp $(TARGET) root@$(IP):$(DIR)

run:
	ssh root@$(IP) /work/hps_gpio

stop:
	ssh root@$(IP) killall hps_gpio

server:
	ssh root@$(IP) gdbserver --multi PORT:$(PORT)

debug:
	exec $(GCC_Linaro)/arm-linux-gnueabihf-gdb -x script.sh

.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *~



