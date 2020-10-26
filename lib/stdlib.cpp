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

#include "../include/lib/stdlib.h"
#include "../include/types.h"

uint8_t Stdlib::is_digit(char ch) {
	if (ch >= '0' && ch <= '9')
        return 1;

    return 0;
}

int32_t Stdlib::atoi(const char* ch) {
	int32_t val;
	
	while(is_digit(*ch)) {
		val *= 10;
		val += (*ch) - '0';
		ch++;
	}
	
	return val;
}

