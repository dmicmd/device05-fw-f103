CC=arm-none-eabi-gcc
CPU=-mcpu=cortex-m3 -mthumb
CFLAGS=$(CPU) -O2 -Wall -ffreestanding -nostdlib
LDSCRIPT=linker.ld

SRC=Core/main.c \
    Core/system_stm32f1xx.c \
    Core/stm32f1xx_it.c \
    Core/delay.c \
    Drivers/BSP/board.c

OBJ=$(SRC:.c=.o)

all: firmware.elf

firmware.elf: $(SRC)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) $(SRC) -o firmware.elf

flash: firmware.elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program firmware.elf verify reset exit"

clean:
	rm -f firmware.elf
