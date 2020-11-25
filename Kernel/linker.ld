ENTRY(boot)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)
SECTIONS {
	. = 0x100000;
	.multiboot.data :
	{
		*(.multiboot.data)
	}
	.multiboot.text :
	{
		*(.multiboot.text)
	}
	_multiboot_end = ABSOLUTE(.);
	. += 0xc0000000;
	.text : AT (ADDR (.text) - 0xC0000000) ALIGN(4096)
	{
		*(.text)
	}
	.rodata : AT (ADDR (.rodata) - 0xC0000000) ALIGN(4096)
	{
		*(.rodata)
	}
	.data : AT (ADDR (.data) - 0xC0000000) ALIGN(4096)
	{
		*(.data)
	}
	.bss : AT (ADDR (.bss) - 0xC0000000) ALIGN(4096)
	{
		*(.bss)
	}
}