# /***********************************************************************/
# /*  "OS compiler make" by Clay Kress                                   */
# /*                                                                     */
# /*  make/make files:  This will compile the entire OS                  */
# /*                       and put it on one easily managable .img file  */
# /*                                                                     */
# /*                                                                     */
# /* Copyright (c) 2022 Clay Kress                                       */
# /*                                                                     */
# /* This file is part of KressOS.                                       */
# /* KressOS is free software: you can redistribute it and/or modify it  */
# /* under the terms of the GNU General Public License as published by   */
# /* the Free Software Foundation, either version 3 of the License, or   */
# /* (at your option) any later version.                                 */
# /*                                                                     */
# /* Foobar is distributed in the hope that it will be useful,           */
# /* but WITHOUT ANY WARRANTY; without even the implied warranty         */
# /* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.             */
# /*                                                                     */
# /* See the GNU General Public License for more details.                */
# /*                                                                     */
# /* You should have received a copy of the GNU General Public License   */
# /* along with Foobar. If not, see <https://www.gnu.org/licenses/>.     */
# /*                                                                     */
# /***********************************************************************/

# These are for C code
driverSRC_C = $(wildcard drivers/*.c)
driverOBJ_C = ${driverSRC_C:.c=.o}

# This gets run if you don't specify a rule
files: catLoad.bin kernel.bin
	rm -rf bootIMG/*.img
	#
	# Making 1 MB disk:
	dd if=/dev/zero of=boot.img bs=1048576 count=1
	#
	# Making boot sector:
	dd if=catLoad.bin of=boot.img conv=notrunc
	
	#
	# Making Kernel
	dd if=kernel.bin of=boot.img conv=notrunc seek=1
	
	od -t x1 -A n boot.img
	mv boot.img bootIMG/

run: files
	qemu-system-x86_64 bootIMG/boot.img
	make clean

disk: files
	sudo dd if=bootIMG/boot.img of=/dev/sdb
	make clean

dism: files
	ndisasm -b 32 kernel.bin > kernel.dis
	make clean
	gedit kernel.dis
	rm kernel.dis

open:
	make clean
	
	
	gedit Makefile &
	sleep 0.5
	
	gedit kernel/kLoad.asm &
	sleep 0.1
	gedit kernel/kernel.c &
	sleep 0.1
	gedit kernel/interrupt.asm &
	sleep 0.5
	
	gedit drivers/* &



# BOOTLOADER COMPILE ###################################################
catLoad.bin: boot/catLoad.asm
	nasm -f bin $^ -o $@
# BOOTLOADER COMPILE ###################################################



# KERNEL COMPILE #######################################################
kernel.bin: kLoad.o kernel.o interrupt.o ${driverOBJ_C}
	ld -m elf_i386 -o $@ -Ttext 0x7e00 $^ --oformat binary

kLoad.o: kernel/kLoad.asm
	nasm -f elf $^ -o $@

kernel.o: kernel/kernel.c
	gcc -m32 -ffreestanding -fno-pie -c $^ -o $@

interrupt.o: kernel/interrupt.asm
	nasm -f elf $^ -o $@
# KERNEL COMPILE #######################################################



# PATTERNS FOR DRIVERS #################################################
# C Pattern for .o files
%.o : %.c
	gcc -m32 -ffreestanding -fno-pie -c $< -o $@
# PATTERNS FOR DRIVERS #################################################



# CLEAN ################################################################
clean:
	rm -rf *.bin *.o
	rm -rf drivers/*.o



