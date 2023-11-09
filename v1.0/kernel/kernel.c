#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"

void main() {
    isr_install();
    irq_install();
    clear_screen();

                                             
    kprint("\n |BGGGGGG!BBBBBBBB|\n"
             " |^5@@@@@@        |\n"
             " |. !#@@@@        |\n"
             " |.  .5@@@        |      BilepterOS Version 1.0 By Prattay Sarkar\n"
             " |.    !#@        |\n"   
             " |.     .PABBBAAAA|              Embrace The Imperfection\n"
             " |.      :#       |\n"   
             " |.      :@@J     |         Copyright (C) 2023 Prattay Sarkar\n"
             " |.      :@@@B    |                All Rights Reserved.\n"
             " |.      :@@@@@   |\n"
             " |.      :@@@@@@B |\n"
             " |AAAAAAAABBBBBBBG|\n\n");          

    kprint("BilepterOS V1.0  Copyright (C) 2023 Prattay Sarkar\n\n");
    kprint("This program comes with ABSOLUTELY NO WARRANTY\n");
    kprint("For More Details, Visit https://www.gnu.org/licenses/gpl-3.0.en.html\n");
    kprint("OR Type LICENSE.\n");
    kprint("This is free software, and you are welcome to redistribute it.\n\n");
    kprint("For Commands List, Type HELP. For Issues, Type ISSUES\n\n");                                                        
    
    kprint_at_green("[BilepterOS]", -1, -1);
    kprint_at_red("$", -1, -1);
    kprint_at_green(": ", -1, -1);
    
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint_at_red("This Computer is now Safe To Shutdown.\n", -1, -1);
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    } else if (strcmp(input, "HELP") == 0){
        kprint("\nCommands: \n\n");
        kprint("HELP: Display This Page\n");
        kprint("PAGE: Display a Requested Malloc\n");
        kprint("LICENSE: Display The GNU General Public Licence.\n");
        kprint("END: Ends The OS Session\n");
        kprint("ISSUES: Shows A List Of Issues.\n");
        kprint("CLS: Clears The Screen\n\n");
    } else if (strcmp(input, "LICENSE") == 0){
        kprint(
            "\nGNU GENERAL PUBLIC LICENSE\n"
            "Version 1.0, 5 November 2023\n"
            "\n"
            "Copyright (C) 2023 Prattay Sarkar\n"
            "\n"
            "This program is free software: you can redistribute it and/or modify\n"
            "it under the terms of the GNU General Public License as published by\n"
            "the Free Software Foundation, either version 3 of the License, or\n"
            "(at your option) any later version.\n"
            "\n"
            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU General Public License for more details.\n"
            "\n"
            "For More Info, See <https://www.gnu.org/licenses/>.\n"
        );
    } else if (strcmp(input, "ISSUES") == 0){
        kprint("\nIssues With This OS:\n\n");
        kprint(" + If You Press Backspace Continuously, It WIll Delete Printed Text.\n");
        kprint(" + It's Just An Project, Not Your Average Daily Driver!\n");
    } else if (strcmp(input, "CLS") == 0){
        clear_screen();
    }
    else {
        kprint_at_red("\n[ERROR]: Bad Command! Refer To HELP Command.\n", -1, -1);
    }

    //kprint("You said: ");
    //kprint(input);

    kprint_at_green("\n[BilepterOS]", -1, -1);
    kprint_at_red("$", -1, -1);
    kprint_at_green(": ", -1, -1);
}
