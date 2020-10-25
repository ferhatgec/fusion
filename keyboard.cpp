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

#include "include/kernel.h"
#include "include/io/keyboard.h"
#include "include/io/layout.h"

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64) {
    while(commandport.Read() & 0x1)
        dataport.Read();
    
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
}

KeyboardDriver::~KeyboardDriver() {}

void printf(char*, unsigned char, unsigned char);
void write_string(int colour, const char *string);

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
    uint8_t key = dataport.Read();
    
    if(key < 0x80) {
        switch(key) {
            case 0x02: printf("1", 2, 0); break;
            case 0x03: printf("2", 2, 0); break;
            case 0x04: printf("3", 2, 0); break;
            case 0x05: printf("4", 2, 0); break;
            case 0x06: printf("5", 2, 0); break;
            case 0x07: printf("6", 2, 0); break;
            case 0x08: printf("7", 2, 0); break;
            case 0x09: printf("8", 2, 0); break;
            case 0x0A: printf("9", 2, 0); break;
            case 0x0B: printf("0", 2, 0); break;

            case 0x10: printf("q", 2, 0); break;
            case 0x11: printf("w", 2, 0); break;
            case 0x12: printf("e", 2, 0); break;
            case 0x13: printf("r", 2, 0); break;
            case 0x14: printf("t", 2, 0); break;
            
	    	case 0x15: 
	    		if(DEFAULT_LAYOUT == "de_DE")
	    			printf("z", 2, 0);
            	else
            		printf("y", 2, 0);
            	break;
            	
            case 0x16: printf("u", 2, 0); break;
            case 0x17: printf("i", 2, 0); break;
            case 0x18: printf("o", 2, 0); break;
            case 0x19: printf("p", 2, 0); break;

            case 0x1E: printf("a", 2, 0); break;
            case 0x1F: printf("s", 2, 0); break;
            case 0x20: printf("d", 2, 0); break;
            case 0x21: printf("f", 2, 0); break;
            case 0x22: printf("g", 2, 0); break;
            case 0x23: printf("h", 2, 0); break;
            case 0x24: printf("j", 2, 0); break;
            case 0x25: printf("k", 2, 0); break;
            case 0x26: printf("l", 2, 0); break;

			case 0x2C: 
	    		if(DEFAULT_LAYOUT == "de_DE")		
            		printf("y", 2, 0);
            	else
            		printf("z", 2, 0);
				break;
            
            case 0x2D: printf("x", 2, 0); break;
            case 0x2E: printf("c", 2, 0); break;
            case 0x2F: printf("v", 2, 0); break;
            case 0x30: printf("b", 2, 0); break;
            case 0x31: printf("n", 2, 0); break;
            case 0x32: printf("m", 2, 0); break;
            case 0x33: printf(",", 2, 0); break;
            case 0x34: printf(".", 2, 0); break;
            case 0x35: printf("-", 2, 0); break;

            case 0x1C: 
            	printf("\n", 2, 0); 
            	printf(BUFFER, 6, 0);
            	break;
            case 0x39: printf(" ", 2, 0); break;

            default: {
                char* foo = "KEYBOARD 0x00 ";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0xF];
                foo[12] = hex[key & 0xF];

		// printf(foo);		
		                
                break;
            }
        }
    }
  
    return esp;
}
