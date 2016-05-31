#include "io.h"
#include "framebuffer.h"

static unsigned int fb_pos_x = 0;
static unsigned int fb_pos_y = 0;

/** fb_write_cell:
 *
 * @param i  framebuffer中的位置
 * @param c  字符
 * @param fg 前景色
 * @param bg 背景色
 */
void fb_write_cell(unsigned short i, char c, unsigned char fg, unsigned char bg)
{
    unsigned char *fb = (unsigned char *)FB_ADDR;
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void fb_move_cursor(unsigned short pos)
{
    if (pos > FB_HEIGHT * (FB_WIDTH - 1))
        return;

    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0xFF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0xFF);
}

void fb_move_next()
{
    if (fb_pos_x >= FB_WIDTH - 1)
        fb_new_line();
    else
        fb_pos_x++;

    fb_move_cursor(fb_pos_x + (fb_pos_y * FB_WIDTH));
}

void fb_new_line()
{
    if (fb_pos_y >= FB_HEIGHT - 1)
        fb_shift_up();
    else
        fb_pos_y++;

    fb_pos_x = 0;
    fb_move_cursor(fb_pos_x + (fb_pos_y * FB_WIDTH));
}

void fb_write(const char *buf, unsigned int len)
{
    unsigned int i;
    for (i = 0; i < len; ++i)
    {
        char c = buf[i];
        if (c == '\n')
        {
            fb_new_line();
        }
        else
        {
            unsigned short pos = fb_pos_x + (fb_pos_y * FB_WIDTH);
            fb_write_cell(pos, c, FB_WHITE, FB_BLACK);
            fb_move_next();
        }
    }
}

void fb_write_str(const char *str)
{
    while (*str)
    {
        char c = *str;
        if (c == '\n')
        {
            fb_new_line();
        }
        else
        {
            unsigned short pos = fb_pos_x + (fb_pos_y * FB_WIDTH);
            fb_write_cell(pos, c, FB_WHITE, FB_BLACK);
            fb_move_next();
        }
        str++;
    }
}

void fb_clear()
{
    fb_pos_x = 0;
    fb_pos_y = 0;

    int i;
    for (i = 0; i < FB_WIDTH * FB_HEIGHT; ++i)
    {
        fb_write_cell(i, ' ', FB_WHITE, FB_BLACK);
    }
    fb_move_cursor(0);
}

void fb_clear_row(unsigned int row)
{
    int i;
    for (i = 0; i < FB_WIDTH; ++i)
    {
        fb_write_cell((row * FB_WIDTH) + i, ' ', FB_WHITE, FB_BLACK);
    }
}

void fb_shift_up()
{
    unsigned char *fb = (unsigned char *)FB_ADDR;

    int i;
    for (i = 0; i < FB_WIDTH * (FB_HEIGHT - 1); ++i)
    {
        fb[i * 2] = fb[i * 2 + FB_WIDTH];
        fb[i * 2 + 1] = fb[i * 2 + FB_WIDTH + 1];
    }
    fb_clear_row(FB_HEIGHT - 1);
}
