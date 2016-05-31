#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#define FB_ADDR              0x000B8000
#define FB_WIDTH             80
#define FB_HEIGHT            25

#define FB_BLACK             0
#define FB_BLUE              1
#define FB_GREEN             2
#define FB_CYAN              3
#define FB_RED               4
#define FB_MAGENTA           5
#define FB_BROWN             6
#define FB_LIGHT_GREY        7
#define FB_DARK_GREY         8
#define FB_LIGHT_BLUE        9
#define FB_LIGHT_GREEN       10
#define FB_LIGHT_CYAN        11
#define FB_LIGHT_RED         12
#define FB_LIGHT_MAGENTA     13
#define FB_LIGHT_BROWN       14
#define FB_WHITE             15

#define FB_COMMAND_PORT      0x03D4
#define FB_DATA_PORT         0x03D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

void fb_write_cell(unsigned short i, char c, unsigned char fg, unsigned char bg);

void fb_move_cursor(unsigned short pos);
void fb_move_next();
void fb_new_line();

void fb_write(const char *buf, unsigned int len);
void fb_write_str(const char *str);

void fb_clear();
void fb_clear_row(unsigned int row);
void fb_shift_up();

#endif
