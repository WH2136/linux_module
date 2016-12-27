obj-m := hello.o

PWD := $(shell pwd)

KERNEL := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL)  M=$(PWD) modules
clean:
	rm -rf *.o *~ core .*.cmd *.mod.c ./tmp_version
