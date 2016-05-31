global loader                        ; ELF入口符号

MAGIC_NUMBER      equ 0x1BADB002
FLAGS             equ 0              ; OS映像需要引导程序提供或支持的特性
CHECKSUM          equ -MAGIC_NUMBER  ; magic + flags + checksum = 0

KERNEL_STACK_SIZE equ 4096

extern kmain

section .bss
align 4
kernel_stack:
  resb KERNEL_STACK_SIZE

section .text
align 4
  dd   MAGIC_NUMBER
  dd   FLAGS
  dd   CHECKSUM

loader:
  mov  esp, kernel_stack+KERNEL_STACK_SIZE
  call kmain
.loop:
  jmp .loop
