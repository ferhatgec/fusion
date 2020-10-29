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

#include "../include/app/calc.h"

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

void Help() {
    printf("Fusion CLI Calculator\n--------------------\n", WHITE_COLOR, 0);

    printf("add = Addition\nsub : Subtraction\nmulti : Multiplication\ndiv : Division\n", WHITE_COLOR, 0); 
}

void RunCalculator() {
	KeyboardInput pass;
    
    Help();

    printf("Enter your choice : ", WHITE_COLOR, 0); 

    string data = pass.GetInput();
    
    printf("(", WHITE_COLOR, 0);
    printf(data, WHITE_COLOR, 0);            
    printf(") [1] : ", WHITE_COLOR, 0);
    
    string first = pass.GetInput();
    int32_t first_int = atoi(first);
    
    printf("(", WHITE_COLOR, 0);
    printf(data, WHITE_COLOR, 0);            
    printf(") [2] : ", WHITE_COLOR, 0);
    
    string second = pass.GetInput();
    int32_t second_int = atoi(second);

    if(compare(data, "add") == 0) printf(itoa(first_int + second_int), WHITE_COLOR, 0);
    else if(compare(data, "sub") == 0) printf(itoa(first_int - second_int), WHITE_COLOR, 0);
    else if(compare(data, "multi") == 0) printf(itoa(first_int * second_int), WHITE_COLOR, 0);
	else if(compare(data, "div") == 0) printf(itoa(first_int / second_int), WHITE_COLOR, 0);

    printf("\n", WHITE_COLOR, 0);
}
