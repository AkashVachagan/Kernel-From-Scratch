BITS 32

section .multiboot
	dd 0x1BADB002
	dd 0x0
	dd - (0x1BADB002 + 0x0)

section .text
extern main
global start

start:
	cli
	lea esp, [stack_pointer + 8192]
	call main
	hlt

section .bss
stack_pointer: resb 8192

