# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source
C_SOURCES = $(wildcard drivers/*.c cpu/*.c kernel/util/*.c kernel/*.c)
HEADERS = $(wildcard drivers/*.h cpu/*.h kernel/util/*.c kernel/*.h)
OBJ_FILES = ${C_SOURCES:.c=.o}

# First rule is the one executed when no parameters are fed to the Makefile
all: run clean

# Notice how dependencies are built as needed
kernel.bin: boot/kernel-entry.o ${OBJ_FILES}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_
	objdump -d $^ > txt

os-image.bin: boot/mbr.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-i386 -fda $<

echo: os-image.bin
	xxd $<

# only for debug
kernel.elf: boot/kernel-entry.o ${OBJ_FILES}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -S -fda os-image.bin -d guest_errors,int &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	gcc -m32 -ffreestanding -c $< -o $@ # -g for debugging

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

%.dis: %.bin
	ndisasm -b 32 $< > $@

clean:
	$(RM) *.bin *.o *.dis *.elf
	$(RM) kernel/*.o
	$(RM) boot/*.o boot/*.bin
	$(RM) drivers/*.o
	$(RM) cpu/*.o
