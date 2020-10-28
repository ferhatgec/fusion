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

#include "../include/lib/string.h"
#include "../include/lib/stdlib.h"

#include "../include/io/input.h"
#include "../include/types.h"
#include "../include/vga/vga.h"
#include "../include/interrupts.h"
#include "../include/port.h"

char *copy(char *s1, const char *s2);
void printf(char* str, unsigned char forecolor, unsigned char backcolor);
void show_buffer();

void RunShell() {
	KeyboardInput input;
	
	while(1) {
		string data = input.GetInput();
	
		if(compare(data, "help") == 0) {
			printf("fufetch : Simple system info application\nhelp: :^)\ntest : string test\n", RED_COLOR, 0);
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

			printf("\n", 0, 0);  
		}

		show_buffer();
	}
}
