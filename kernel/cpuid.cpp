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

icpuid_t detect_cpu(void) {
    unsigned long ebx, unused;
    icpuid_t i_cpu;    

    cpuid(0, unused, ebx, unused, unused);

    switch(ebx) {
        case INTEL_MAGIC_CODE:
            i_cpu = intel();
            break;
        default:
            printf("Generic (x86)\n", WHITE_COLOR, 0);
            break;
    }

    return i_cpu;
}

icpuid_t intel() {
    unsigned long eax, ebx, ecx, edx, max_eax,
        signature, unused;

    icpuid_t icpu;

    int extended_family = -1;

    cpuid(1, eax, ebx, unused, unused);

    icpu.model = (eax >> 4) & 0xf;
    icpu.family = (eax >> 8) & 0xf;
    icpu.type = (eax >> 12) & 0x3;
    icpu.brand = ebx & 0xff;
    icpu.stepping = eax & 0xf;
    icpu.reserved = eax >> 14;
    signature = eax;

    return icpu;
}

cpuid_t get_cpuid(icpuid_t _icpuid) {
    cpuid_t _cpuid;

    switch(_icpuid.type) {
        case 0:
            _cpuid.type = "Original OEM";
            break;
        case 1:
            _cpuid.type = "Overdrive";
            break;       
        case 2:
            _cpuid.type = "Dual-capable";
            break;
        case 3:
            _cpuid.type = "Reserved";
            break;
    }

    switch(_icpuid.family) {
		case 3:
            _cpuid.family = "i386";		    
            break;
		case 4:
            _cpuid.family = "i486";		    
            break;
		case 5:
            _cpuid.family = "Pentium";
		    break;
		case 6:
            _cpuid.family = "Pentium Pro";
		    break;
		case 15:
            _cpuid.family = "Pentium 4";
            break;
    }

    return _cpuid;
}


void print_type() {
    icpuid_t icpu = detect_cpu();

    cpuid_t cpu_type = get_cpuid(icpu);
    
    printf(cpu_type.type, WHITE_COLOR, 0);
}

void print_family() {
    icpuid_t icpu = detect_cpu();

    cpuid_t cpu_family = get_cpuid(icpu);
    
    printf(cpu_family.family, WHITE_COLOR, 0);
}
