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

#include "../include/lib/string.h"
#include "../include/types.h"

uint16_t length(string ch) {
	for(uint16_t len = 0; ch[len] != '\0'; len++)
	
	return len;
}

uint8_t equal(string ch1, string ch2) {
	uint8_t result, size;
	
	result = 1;
	size = length(ch1);
	
	if(size != length(ch2)) 
		result = 0;
	else {
		for(uint8_t i = 0; i <= size; i++)
			if(ch1[i] != ch2[i]) 
				result = 0;
	}
	
	return result;
}

uint8_t find(string data, string ch) {
	uint8_t len = 0;
    
    do { len++; } while(ch[len] != '\0');
    
    if (!len)
        return 0;
        
    for (int i = 0; i < len; i ++) {
       	if (data[i] == ch[0]) {
			int j = 0;
            
            for (; j < len; j++)
                if (data[i + j] != ch[j]) break;
                	 
            if (j == len)
				return i;
        }            
	}        

    return -1;
}

int8_t compare(string str1, string str2) {
	int16_t res = 0;
	
	while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2)
		++str1, ++str2;

	if (res < 0)
		res = -1;
	if (res > 0)
		res = 1;

	return res;
}
