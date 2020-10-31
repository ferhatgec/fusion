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


/* 
    Some of things from Intel's Documentations and OSDev topics. 
*/

#include "../include/cpu/cpuid.h"
#include "../include/kernel.h"
#include "../include/types.h"
#include "../include/vga/vga.h"

#define INTEL_MAGIC_CODE 0x756e6547
#define AMD_MAGIC_CODE 0x68747541


void printf(char* str, unsigned char forecolor, unsigned char backcolor);

int detect_cpu(void) {
    unsigned long ebx, unused;
    
    cpuid(0, unused, ebx, unused, unused);

    switch(ebx) {
        case INTEL_MAGIC_CODE:
            intel();
            break;
        default:
            printf("Generic (x86)\n", WHITE_COLOR, 0);
            break;
    }

    return 0;
}

int intel() {
    unsigned long eax, ebx, ecx, edx, max_eax,
        signature, unused;

    int model, family, type, brand, stepping, reserved;
    int extended_family = -1;

    cpuid(1, eax, ebx, unused, unused);

    model = (eax >> 4) & 0xf;
    family = (eax >> 8) & 0xf;
    type = (eax >> 12) & 0x3;
    brand = ebx & 0xff;
    stepping = eax & 0xf;
    reserved = eax >> 14;
    signature = eax;

    switch(type) {
        case 0:
            printf("Original OEM", WHITE_COLOR, 0);
            break;
       case 1:
            printf("Overdrive", WHITE_COLOR, 0);
            break;       
       case 2:
            printf("Dual-capable", WHITE_COLOR, 0);
            break;
        case 3:
            printf("Reserved", WHITE_COLOR, 0);
            break;
    }
}

