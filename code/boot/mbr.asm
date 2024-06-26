[bits 16]	 				; 16bit real mode
[org 0x7c00] 				; set assembler location counter,
							; mempory address where the BIOS is placing the bootloader

; where to load the kernel to
KERNEL_OFFSET equ 0x1000

; BIOS sets boot drive in 'dl'; store for later use
mov [BOOT_DRIVE], dl

; setup stack
mov bp, 0x9000
mov sp, bp

call load_kernel
call switch_to_32bit

jmp $

%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/switch-to-32bit.asm"

[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET 	; bx -> destination
	mov dh, 2			  	; dh -> num sectors
	mov dl, [BOOT_DRIVE]  	; dl -> disk
	call disk_load
	ret

[bits 32] ; 32 bit protected mode
BEGIN_32BIT:
	call KERNEL_OFFSET 		; give control to the kernel
	jmp $			   		; loop in case kernel returns
	
; boot drive variable
BOOT_DRIVE db 0

; padding
times 510 - ($-$$) db 0

; magic standard PC boot number
dw 0xaa55
