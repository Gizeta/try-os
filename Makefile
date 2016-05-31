OBJECTS = loader.o io.o framebuffer.o kmain.o
CC      = gcc
CFLAGS  = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS      = nasm
ASFLAGS = -f elf

all : kernel.elf

kernel.elf : $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY : iso
iso : kernel.elf
	cp kernel.elf iso/boot/
	genisoimage -R                   \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot                \
		-boot-load-size 4            \
		-A NeOS                      \
		-input-charset utf8          \
		-quiet                       \
		-boot-info-table             \
		-o os.iso                    \
		iso

.PHONY : clean
clean :
	-rm *.o  *.elf iso/boot/kernel.elf os.iso
