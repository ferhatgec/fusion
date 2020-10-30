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


#include "../include/types.h"
#include "../include/time.h"
#include "../include/lib/stdlib.h"
#include "../include/vga/vga.h"

void printf(char* str, unsigned char forecolor, unsigned char backcolor);

inline unsigned char inb(unsigned short port);
inline void outb(unsigned short port, unsigned char value); 

bool is_cmos_update() {
    outb(CMOS_ADDRESS, 0x0A);
    return (inb(CMOS_DATA) & 0x80);
}

uint8_t get_realtime_reg(s32 reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

time_t time() {
    while (is_cmos_update());
    
    time_t time;

    time.second = from_bcd(get_realtime_reg(TIME_SECOND));
    time.minute = from_bcd(get_realtime_reg(TIME_MINUTE));
    time.hour = from_bcd(get_realtime_reg(TIME_HOUR));
    time.day = from_bcd(get_realtime_reg(TIME_DAY));
    time.month = from_bcd(get_realtime_reg(TIME_MONTH));
    time.year = from_bcd(get_realtime_reg(TIME_YEAR));

    return time;
}

uint32_t time_get(uint32_t selector) {
    while (is_cmos_update());
    return from_bcd(get_realtime_reg(selector));
}

void PrintYear() {
    printf(itoa(time_get(TIME_MONTH)), WHITE_COLOR, 0);
    printf("/", WHITE_COLOR, 0);
    printf(itoa(time_get(TIME_YEAR)), WHITE_COLOR, 0);
}
