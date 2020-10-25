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

#ifndef MOUSE_H
#define MOUSE_H

#include "../types.h"
#include "../port.h"
#include "../interrupts.h"

class MouseDriver : public InterruptHandler {
	Port8Bit dataport;
	Port8Bit commandport;
       
    uint8_t buffer[3];
	uint8_t offset;
	uint8_t buttons;

	int8_t x, y;
public:
	MouseDriver(InterruptManager* manager);
	~MouseDriver();
	
	virtual uint32_t HandleInterrupt(uint32_t esp);
};

#endif // MOUSE_H
