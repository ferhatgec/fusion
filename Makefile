GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

app = shell.o fufetch.o login.o
lib = string.o stdlib.o
objects = loader.o gdt.o port.o interruptstubs.o mouse.o interrupts.o input.o keyboard.o kernel.o

run: fusion.iso
	qemu-system-i386 -m 512M -cdrom fusion.iso
	
%.o: app/%.cpp
	gcc $(GCCPARAMS) -c -o $@ $<
	
%.o: lib/%.cpp
	gcc $(GCCPARAMS) -c -o $@ $<
	
%.o: kernel/%.cpp
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

fusion.bin: linker.ld $(objects) $(lib) $(app)
	ld $(LDPARAMS) -T $< -o $@ $(objects) $(lib) $(app)

fusion.iso: fusion.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp fusion.bin iso/boot/fusion.bin
	echo 'set timeout=5'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "Fegeya Fusion" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/fusion.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub2-mkrescue --output=fusion.iso iso
	rm -f $(objects) $(lib) $(app) fusion.bin
	rm -rf iso

install: fusion.bin
	sudo cp $< /boot/fusion.bin

.PHONY: clean
clean:
	rm -f $(objects) $(lib) $(app) fusion.bin fusion.iso
