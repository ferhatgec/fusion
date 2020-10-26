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

#include "../include/lib/string.h"
#include "../include/lib/stdlib.h"

#include "../include/io/input.h"
#include "../include/types.h"
#include "../include/vga/vga.h"
#include "../include/interrupts.h"
#include "../include/port.h"

void printf(char* str, unsigned char forecolor, unsigned char backcolor);
void show_buffer();

void RunShell() {
	KeyboardInput input;
	
	while(1) {
		string data = input.GetInput();
	
		if(equal(data, "help") == 1) {
			printf("\nHmm. Fusion has only 'help' command, srry\n", RED_COLOR, 0);
		}

		show_buffer();
	}
}
