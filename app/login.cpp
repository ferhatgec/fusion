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

#include "../include/app/login.h"

#include "../include/lib/string.h"
#include "../include/lib/stdlib.h"

#include "../include/io/input.h"
#include "../include/types.h"
#include "../include/vga/vga.h"
#include "../include/interrupts.h"
#include "../include/port.h"
#include "../include/kernel.h"

void printf(char* str, unsigned char forecolor, unsigned char backcolor);
void show_buffer();
void enable_cursor();

int8_t RunLogin() {
	KeyboardInput pass;
    
    	enable_cursor();
	
	printf("Welcome, ", 3, 0);
	printf(DEFAULT_USERNAME, 4, 0);
	
	string _pass;
	
	do {
		printf("\nPassword: ", 5, 0);
	
		_pass = pass.GetInput();
		
	} while(compare(_pass, DEFAULT_PASS) != 0);

	printf("Logged in.\n", LIGHT_GREEN_COLOR, 0);
	
	return 1;
}
