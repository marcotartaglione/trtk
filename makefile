KERNEL := build/kernel.bin

LINKER_SCRIPT := linker.ld

C_SOURCES := $(shell find boot kernel -name '*.c')
ASM_SOURCES := $(shell find boot kernel -name '*.asm')

C_OBJECTS := $(patsubst %.c, build/%.o, $(C_SOURCES))
ASM_OBJECTS := $(patsubst %.asm, build/%.o, $(ASM_SOURCES))

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

.PHONY: all clean qemu qemu-gdb

all: $(KERNEL)

clean:
	@rm -rf build serial.log

qemu: $(KERNEL)
	qemu-system-i386 -vga std -s -serial file:serial.log -kernel $(KERNEL)

qemu-gdb: $(KERNEL)
	qemu-system-i386 -vga std -s -serial file:serial.log -S -kernel $(KERNEL)

$(KERNEL): $(OBJECTS)
	@mkdir -p $(dir $@)
	ld -m elf_i386 -n -T $(LINKER_SCRIPT) -o $@ $^

build/%.o: %.c
	@mkdir -p $(dir $@)
	gcc -m32 -ffreestanding -O2 -Wall -Wextra -g -c $< -o $@

build/%.o: %.asm
	@mkdir -p $(dir $@)
	nasm -felf32 -g -F dwarf $< -o $@
