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

#include "../include/app/shell.h"
#include "../include/app/fufetch.h"
#include "../include/app/login.h"
#include "../include/app/calc.h"

#include "../include/lib/string.h"
#include "../include/lib/stdlib.h"

#include "../include/io/input.h"
#include "../include/types.h"
#include "../include/vga/vga.h"
#include "../include/interrupts.h"
#include "../include/port.h"


void InitPrint(string message, bool ok);
void printf(char* str, unsigned char forecolor, unsigned char backcolor);
void show_buffer();

void HelpFunction() {
    printf("fufetch : Simple system info application\n", RED_COLOR, 0);
    printf("calc : Calculator\n", RED_COLOR, 0);
    printf("logout : Logout from user\n", RED_COLOR, 0);
    printf("reboot : Reboot the system\n", RED_COLOR, 0);
    printf("test : String test\n", RED_COLOR, 0);
	printf("help: :^)\n", RED_COLOR, 0);
}

void reboot() {
    uint8_t good = 0x02;
    while (good & 0x02)
        good = Port8Bit::Read8(0x64);
    Port8Bit::Write8(0x64, 0xFE);
    InitPrint("If you see this message, power off this PC.", false);
loop:
    InitPrint("Halt the CPU", true);
    asm volatile ("hlt"); /* Halt the CPU */
    goto loop; /* Halt again */
}    

int8_t RunShell() {
	KeyboardInput input;
	
    int8_t logout = 0;

	do {
		string data = input.GetInput();
	
		if(compare(data, "help") == 0) {
			HelpFunction();	
		} else if(compare(data, "fufetch") == 0) {
			RunFuFetch();
		} else if(compare(data, "test") == 0) {
			char* data_;
			
			printf("This is inputted text: ", WHITE_COLOR, 0);
			printf(data, WHITE_COLOR, 0);
			
			printf("\nCopying.\n", WHITE_COLOR, 0);
			
			copy(data_, data);
			
			printf("This is copied string (data_) : ", WHITE_COLOR, 0);
			
			printf(data_, WHITE_COLOR, 0);
			
			printf("\nThis is length of string (data_) : ", WHITE_COLOR, 0);
			printf(itoa(length(data_)), WHITE_COLOR, 0);
			
			printf("\n", 0, 0);  
		} else if(compare(data, "calc") == 0) {
	        RunCalculator();
		} else if(compare(data, "logout") == 0) {
	        logout = 1;		
        } else if(compare(data, "reboot") == 0) {
            reboot();
        } else if(compare(data, "") != 0) {
			printf("Fusion: Command not available -> ", RED_COLOR, 0);
			printf(data, WHITE_COLOR, 0);
			printf("\n", 0, 0);	
		}
			
		if(logout == 0) show_buffer();
	} while(logout == 0);

    if(RunLogin() == 1) logout = 0;
}
