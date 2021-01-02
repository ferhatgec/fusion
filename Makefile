GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386
MKRESCUE = grub2-mkrescue

app = shell.o calc.o fufetch.o login.o date.o
lib = string.o stdlib.o
objects = loader.o gdt.o port.o interruptstubs.o mouse.o interrupts.o input.o keyboard.o time.o \
          cpuid.o kernel.o

run: fusion.iso
	qemu-system-i386 -m 512M -cdrom fusion.iso
	
%.o: app/%.cpp
	$(CC) $(GCCPARAMS) -c -o $@ $<
	
%.o: lib/%.cpp
	$(CC) $(GCCPARAMS) -c -o $@ $<
	
%.o: kernel/%.cpp
	$(CC) $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASPARAMS) -o $@ $<

fusion.bin: linker.ld $(objects) $(lib) $(app)
	$(LD) $(LDPARAMS) -T $< -o $@ $(objects) $(lib) $(app)

fusion.iso: fusion.bin
	mkdir -p iso
	mkdir -p iso/boot
	mkdir -p iso/boot/grub
	cp fusion.bin iso/boot/fusion.bin
	echo 'set timeout=5'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "Fegeya Fusion" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/fusion.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	${MKRESCUE} --output=fusion.iso iso
	${RM} $(objects) $(lib) $(app) fusion.bin
	rm -rf iso

install: fusion.bin
	sudo cp $< /boot/fusion.bin

.PHONY: clean
clean:
	$(RM) $(objects) $(lib) $(app) fusion.bin fusion.iso
	rm -rf iso
