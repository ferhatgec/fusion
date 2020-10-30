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


#ifndef TIME_H
#define TIME_H

#include "types.h"

#define TIME_SECOND 0x00
#define TIME_MINUTE 0x02
#define TIME_HOUR 0x04
#define TIME_DAY 0x07
#define TIME_MONTH 0x08
#define TIME_YEAR 0x09

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

#define from_bcd(val)  ((val / 16) * 10 + (val & 0xf))

typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint32_t year;
} time_t;
 

time_t time();

uint32_t time_get(uint32_t selector);

void time_task();

extern void PrintYear();

#endif // TIME_H
