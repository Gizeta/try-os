void kmain()
{
    int i;
    char *fb = (char *)0x000B8000;
    fb[0] = 'H';
    fb[1] = 0x28;
    fb[2] = 'E';
    fb[3] = 0x28;
    fb[4] = 'L';
    fb[5] = 0x28;
    fb[6] = 'L';
    fb[7] = 0x28;
    fb[8] = 'O';
    fb[9] = 0x28;
    fb[10] = ' ';
    fb[11] = 0x28;
    fb[12] = 'O';
    fb[13] = 0x28;
    fb[14] = 'S';
    fb[15] = 0x28;
    for (i = 16; i < 32; i += 2)
    {
        fb[i] = ' ';
        fb[i + 1] = 0x0F;
    }
}
