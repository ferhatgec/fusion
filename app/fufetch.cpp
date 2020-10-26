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

#include "../include/app/fufetch.h"

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

string Fusion_logo = "       _______\n"
		     "      / _____/\n"
		     "     / /_____\n"
                     "__  /  _____/\n"
                     "\\ \\/  /\n"
                     " \\/__/\n";


void RunFuFetch() {
	printf("       _______\n      / _____/\n     / /_____  ", GREEN_COLOR, 0);
	printf("Username: ", CYAN_COLOR, 0);
	printf(DEFAULT_USERNAME, LIGHT_BLUE_COLOR, 0);
	printf("\n__  /  _____/  ", GREEN_COLOR, 0);
	printf("Hostname: ", CYAN_COLOR, 0);
	printf(DEFAULT_HOSTNAME, LIGHT_BLUE_COLOR, 0);
	printf("\n\\ \\/  /  ", GREEN_COLOR, 0);
	printf("      Fusion version: ", CYAN_COLOR, 0);
	printf(FUSION_VERSION, LIGHT_BLUE_COLOR, 0);
	printf("\n \\/__/\n", GREEN_COLOR, 0);
}
