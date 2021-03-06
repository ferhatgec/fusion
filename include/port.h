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

#ifndef PORT_H
#define PORT_H

#include "types.h"

// FIXME: Must be virtual (currently isnt because the kernel has no memory management yet)

class Port {
public:
	Port(uint16_t portnumber);
	~Port();
	uint16_t portnumber;
};

    
class Port8Bit : public Port {
public:
	Port8Bit(uint16_t portnumber);
	~Port8Bit();

	virtual uint8_t Read();
	virtual void Write(uint8_t data);

	static inline uint8_t Read8(uint16_t _port) {
		uint8_t result;
		__asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
		return result;
	}

	static inline void Write8(uint16_t _port, uint8_t _data) {
		__asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
	}
};


class Port8BitSlow : public Port8Bit {
public:
	Port8BitSlow(uint16_t portnumber);
	~Port8BitSlow();

	virtual void Write(uint8_t data);

	static inline void Write8Slow(uint16_t _port, uint8_t _data) {
		__asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
	}
};


class Port16Bit : public Port {
public:
	Port16Bit(uint16_t portnumber);
	~Port16Bit();

	virtual uint16_t Read();
	virtual void Write(uint16_t data);

	static inline uint16_t Read16(uint16_t _port) {
		uint16_t result;
		__asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
		return result;
	}
           
	static inline void Write16(uint16_t _port, uint16_t _data) {
		__asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
	}
};

class Port32Bit : public Port {
public:
	Port32Bit(uint16_t portnumber);
	~Port32Bit();

	virtual uint32_t Read();
	virtual void Write(uint32_t data);

	static inline uint32_t Read32(uint16_t _port) {
		uint32_t result;
		__asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
		
		return result;
	}

	static inline void Write32(uint16_t _port, uint32_t _data) {
		__asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
	}
};

#endif // PORT_H
