
obj-m := ht16k33.o
MODULES_BUILD := /lib/modules/$(shell uname -r)/build
MODULE_DIR := $(shell pwd)

all:
	$(MAKE) -C $(MODULES_BUILD) M=$(MODULE_DIR) modules

clean:
	$(MAKE) -C $(MODULES_BUILD) M=$(MODULE_DIR) clean

