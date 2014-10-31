CC      = arm-linux-gcc
OBJCOPY = arm-linux-objcopy
CFLAGS  = -O2 -ffreestanding -Wall -Werror -nostdinc -I ../../part1/libc/include -I ../uboot/include
LDFLAGS = -nostdlib -Wl,-Ttext,$(LOAD_ADDR)

LOAD_ADDR = 0xa2000000

STUBS = ../uboot/stubs.o

CRT0    = ../../part1/libc/crt0.o
LDLIBS  = ../../part1/libc/libc.a

objects = echo.o

default: echo.bin

.PHONY: default clean clobber

echo.bin: echo
	$(OBJCOPY) -O binary $< $@

echo: $(objects)
	$(CC) $(LDFLAGS) -o $@ $(CRT0) $^ $(LDLIBS) $(STUBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f echo $(objects)

clobber: clean
	rm -f echo.bin
