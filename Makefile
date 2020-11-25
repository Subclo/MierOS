QEMU_BIN = qemu-system-i386

MAX_RAM = 128M

QEMU_FLAGS = -s -m $(MAX_RAM) \
			-d guest_errors \
			-d cpu_reset \
			-smp 2 \
			-device VGA,vgamem_mb=64 \
			-drive file=mieros.iso,format=raw,index=0,media=disk \
			-device ich9-ahci \
			-usb \
			-debugcon stdio \
			-soundhw pcspk \
			-device sb16

.PHONY: mieros.iso
mieros.iso:
	mkdir -p iso/boot/grub

	echo 'set timeout=10' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry MierOS {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg

	cd Kernel; make install

	grub-mkrescue --output=$@ iso -iso-level 2
	rm -rf iso

.PHONY: run
run:
	make mieros.iso
	$(QEMU_BIN) $(QEMU_FLAGS)

all:
	make mieros.iso

.PHONY: clean
clean:
	cd Kernel; make clean

