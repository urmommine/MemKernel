ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
	obj-$(CONFIG_MEMKERNEL)  := memkernel.o
	memkernel-y := memory.o process.o entry.o
else
# normal makefile
ifeq ($(KDIR),)
	$(Error: KDIR is not set.)
endif
default:
	make -C $(KDIR) M=$(PWD) ARCH=arm64 SUBARCH=arm64 modules
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers .*.cmd
endif