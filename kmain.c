#include "io.h"
#include "framebuffer.h"

void kmain()
{
    fb_clear();
    fb_write_str("HELLO OS");
}
