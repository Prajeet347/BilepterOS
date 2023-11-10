#include "stdint.h"
#include "stdio.h"

void _cdecl cstart_(uint16_t bootDrive)
{
    puts(   "\r\nBilepterOS V1.0  Copyright (C) 2023 Prattay Sarkar\r\n\n"
            "This program comes with ABSOLUTELY NO WARRANTY\r\n"
            "For More Details, Visit https://www.gnu.org/licenses/gpl-3.0.en.html\r\n"
            "This is free software, and you are welcome to redistribute it.\r\n\n"
    );
    for (;;);
}
