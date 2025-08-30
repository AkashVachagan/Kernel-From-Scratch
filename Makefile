CP := cp
RM := rm -rf
MKDIR := mkdir -pv

# Output binary for the kernel
BIN = kernel.bin
CFG = grub.cfg
ISO_PATH := isodir
BOOT_PATH := $(ISO_PATH)/boot
GRUB_PATH := $(BOOT_PATH)/grub

CC = gcc
ASM = nasm
LD = ld
CFLAGS = -m32 -ffreestanding -O2 -Wall -Iinclude
LDFLAGS = -m elf_i386 -T linker.ld

# Source files
SRC_C = $(wildcard kernel/*.c drivers/*.c)
OBJ_C = $(SRC_C:.c=.o)
OBJ_ASM = boot/boot.o
OBJ = $(OBJ_C) $(OBJ_ASM)

.PHONY: all
all: $(BIN) iso
	@echo "Build completed successfully!"

# Assemble bootloader
boot/boot.o: boot/boot.asm
	$(ASM) -f elf32 $< -o $@

# Compile C sources
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files into kernel.bin
$(BIN): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

# Create ISO with GRUB
iso: $(BIN) $(CFG)
	$(MKDIR) $(GRUB_PATH)
	$(CP) $(BIN) $(BOOT_PATH)
	$(CP) $(CFG) $(GRUB_PATH)
	grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	grub-mkrescue -o my-kernel.iso $(ISO_PATH)

# Run in QEMU
.PHONY: run
run: iso
	qemu-system-i386 -cdrom my-kernel.iso -boot d -m 512M

# Clean build artifacts safely
.PHONY: clean
clean:
	$(RM) boot/boot.o
	$(RM) kernel/*.o drivers/*.o
	$(RM) $(BIN)
	$(RM) my-kernel.iso
	$(RM) -r $(ISO_PATH)

