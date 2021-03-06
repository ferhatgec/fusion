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

#ifndef CPUID_H
#define CPUID_H

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

typedef struct {
    int model;
    int family;
    int type;
    int brand;
    int stepping;
    int reserved; 
} icpuid_t;

typedef struct {
    char* model;
    char* family;
    char* type;
    char* brand;
    char* stepping;
    char* reserved;
} cpuid_t;


cpuid_t get_cpuid(icpuid_t);

/* TODO: List of AMD & Intel ID's. */
icpuid_t detect_cpu(void);
icpuid_t intel(void);

void print_type();
void print_family();

#endif // CPUID
