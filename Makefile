#This is how your cross compiler directory needs to be set up
CC=cc/bin/i686-elf-gcc

DEPS=kernel/*.c shell/*.c mm/*.c
CCFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib
LINKER=cc/LINKER.ld				#I will eventually move this.
INCLUDE=include/

output/kernel.bin: compile
	@(${CC} -T ${LINKER} -o $@ ${LDFLAGS} output/*.o)

compile: ${DEPS}
	@(nasm -f elf32 -o output/start.o boot/grub.asm)
	@(${CC} -I${INCLUDE} -c $^ ${CCFLAGS})
	@(mv *.o output)

clean:
	@(rm -rf output/*)

iso: output/kernel.bin
	@(if grub-file --is-x86-multiboot output/kernel.bin; then echo "The file is multiboot."; else echo "The file is NOT multiboot!"; exit; fi)
	@(mkdir -p iso/boot/grub)
	@(cp output/kernel.bin iso/boot/kernel.bin)
	@(cp boot/grub.cfg iso/boot/grub/grub.cfg)
	@(grub-mkrescue -o output/cdrom.iso iso)
	@(rm -rf iso)
