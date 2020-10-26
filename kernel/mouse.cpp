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

#include "../include/io/mouse.h"

MouseDriver::MouseDriver(InterruptManager* manager) : InterruptHandler(manager, 0x2C),
	dataport(0x60),
	commandport(0x64) {
	
	uint16_t* VideoMemory = (uint16_t*)0xB8000;
	offset = 0;
	buttons = 0;
	
	// Default positions
	x = 40;
	y = 12;
	
	VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);

	commandport.Write(0xA8);
	commandport.Write(0x20); // command 0x60 = read controller command byte
       
	uint8_t status = dataport.Read() | 2;
	commandport.Write(0x60); // command 0x60 = set controller command byte
	dataport.Write(status);

	commandport.Write(0xD4);
	dataport.Write(0xF4);
	dataport.Read();
}

MouseDriver::~MouseDriver() {}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp) {
	uint8_t status = commandport.Read();
	
	if(!(status & 0x20)) return esp;
	
	buffer[offset] = dataport.Read();
        offset = (offset + 1) % 3;

        if(offset == 0) {
            if(buffer[1] != 0 || buffer[2] != 0) {
                static uint16_t* VideoMemory = (uint16_t*)0xb8000;
                
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                    | (VideoMemory[80*y+x] & 0xF000) >> 4
                                    | (VideoMemory[80*y+x] & 0x00FF);

                x += buffer[1];
                
                if(x >= 80) x = 79;
                if(x < 0) x = 0;
                
                y -= buffer[2];
                
                if(y >= 25) y = 24;
                if(y < 0) y = 0;

                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                    | (VideoMemory[80*y+x] & 0xF000) >> 4
                                    | (VideoMemory[80*y+x] & 0x00FF);
            }
	}
	
	return esp;
}
