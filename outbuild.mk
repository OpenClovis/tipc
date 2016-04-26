tipc-y := $(patsubst %.c,%.o,$(wildcard *.c))
$(info $(tipc-y))

all:
	make -C /lib/modules/$(shell uname -r)/build "CFLAGS_tipc.o:=-ITEST" M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
