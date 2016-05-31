global inb
global outb

inb:
  mov  dx, [esp+4]
  in   al, dx
  ret

; outb - 向IO口发送1字节数据
; stack: [esp+8] 数据
;        [esp+4] IO口
;        [esp]   返回地址
outb:
  mov  al, [esp+8]
  mov  dx, [esp+4]
  out  dx, al
  ret
