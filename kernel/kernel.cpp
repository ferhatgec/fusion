/*
 * Copyright (c) 2020 Ferhat Gecdogan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../include/kernel.h"
#include "../include/types.h"
#include "../include/gdt/gdt.h"
#include "../include/interrupts.h"
#include "../include/io/keyboard.h"
#include "../include/io/mouse.h"
#include "../include/vga/vga.h"
#include "../include/lib/string.h"
#include "../include/lib/stdlib.h"

#include "../include/app/shell.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

inline void outb(unsigned short port, unsigned char value) {
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

inline unsigned char inb(unsigned short port) {
	unsigned char ret;
	asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );

	return ret;
}
    


void enable_cursor() {
    outb(0x3D4, 0x0A);
    char curstart = inb(0x3D5) & 0x1F; // get cursor scanline start

    outb(0x3D4, 0x0A);
    outb(0x3D5, curstart | 0x20); // set enable bit
}


void update_cursor(int x, int y) {
	uint16_t pos = y * 80 + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}



void WriteCharacter(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y) {
     uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
     volatile uint16_t * where;
     where = (volatile uint16_t *)0xB8000 + (y * 80 + x) ;
     *where = c | (attrib << 8);
}

void printf(char* str, unsigned char forecolor, unsigned char backcolor) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i]) {
            case '\n':
                x = 0;
                y++;
                break;
            default:
            	WriteCharacter(str[i], forecolor, backcolor, x, y);
                //VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80) {
            x = 0;
            y++;
        }

        if(y >= 25) {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void show_buffer() {
	/* Same with rcolorized */
    printf(DEFAULT_USERNAME, BROWN_COLOR, 0);
    printf(BUFFER, YELLOW_COLOR, 0);
    printf(DEFAULT_HOSTNAME, LIGHT_GREEN_COLOR, 0);
    
    printf(BUFFER_SIGN, LIGHT_BLUE_COLOR, 0);
}
    
extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/) {    
    string str = "Hey user, Welcome to Fegeya Fusion!\n";
    
    printf(str, 10, 0);
    
    show_buffer();
    
    enable_cursor();
    
    GlobalDescriptorTable gdt;
 
    InterruptManager interrupts(0x20, &gdt);
    
    /* Keyboard & mouse handle interrupts & drivers (Generic PS/2) */
    KeyboardDriver keyboard(&interrupts);
    
    RunShell();
    
    while(1);
}
