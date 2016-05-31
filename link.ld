ENTRY(loader)              /* 入口标签的名字 */

SECTIONS {
  . = 0x00100000;          /* 内核的内存地址需大于或等于1MB */

  .text ALIGN (0x1000):    /* 4kb对齐 */
  {
    *(.text)               /* 全部.text段 */
  }

  .rodata ALIGN (0x1000):
  {
    *(.rodata*)
  }

  .data ALIGN (0x1000):
  {
    *(.data)
  }

  .bss ALIGN (0x1000):
  {
    *(COMMON)
    *(.bss)
  }
}
