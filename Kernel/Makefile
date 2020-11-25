SOURCES = obj/entry.o \
		  obj/kernel.o \
		  obj/common/print.o \
		  obj/system/gdt.o \
		  obj/system/gdta.o \
		  obj/common/string.o

CC = i686-elf-g++
AS = nasm
LD = ld

LD_SCRIPT = linker.ld

obj/%.o: sources/%.s
	mkdir -p $(@D)
	$(AS) -felf32 -o $@ $<

obj/%.o: sources/%.cpp
	mkdir -p $(@D)
	$(CC) -m32 -c -o $@ $< -Iinclude

kernel.bin: $(SOURCES)
	$(LD) -melf_i386 -T $(LD_SCRIPT) -o $@ $(SOURCES)

all:
	make kernel.bin

.PHONY: install
install:
	make
	cp kernel.bin ../iso/boot

.PHONY: clean
clean:
	rm -rf obj
	rm kernel.bin