ASM = nasm
S_SOURCE=$(wildcard src/boot/*.s)
S_OBJECT=$(patsubst src/%.s,objects/%.bin,$(S_SOURCE))

run:all
	bochs -f script/bochsrc

all:update

update:$(S_OBJECT)
	dd if=objects/boot/boot.bin of=hd64M.img  bs=512 count=1 conv=notrunc
	dd if=objects/boot/loader.bin of=hd64M.img  bs=512 count=2 seek=1 conv=notrunc


objects/boot/%.bin:src/boot/%.s
	mkdir -p $(@D)
	$(ASM) -I include -o $@ $<

clean:
	rm -rf objects