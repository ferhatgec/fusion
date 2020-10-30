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

#include "../include/app/date.h"

#include "../include/time.h"
#include "../include/types.h"
#include "../include/vga/vga.h"
#include "../include/lib/stdlib.h"

void printf(char* str, unsigned char forecolor, unsigned char backcolor);

void RunDate() {
    printf(itoa(time_get(TIME_DAY)), WHITE_COLOR, 0);
    printf("/", WHITE_COLOR, 0);

    printf(itoa(time_get(TIME_MONTH)), WHITE_COLOR, 0);
    printf("/", WHITE_COLOR, 0);

    printf(itoa(time_get(TIME_YEAR)), WHITE_COLOR, 0);
    
    printf(" : ", WHITE_COLOR, 0);

    printf(itoa(time_get(TIME_HOUR)), WHITE_COLOR, 0);
    printf(":", WHITE_COLOR, 0);   
    
    printf(itoa(time_get(TIME_MINUTE)), WHITE_COLOR, 0);
    printf(":", WHITE_COLOR, 0);

    printf(itoa(time_get(TIME_SECOND)), WHITE_COLOR, 0);
    
    printf("\n", WHITE_COLOR, 0);
}
