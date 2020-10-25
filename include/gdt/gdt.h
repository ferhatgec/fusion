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

#ifndef GDT_H
#define GDT_H

#include "../types.h"
    
class GlobalDescriptorTable {
public:
	class SegmentDescriptor {
		private:
			uint16_t limit_lo;
            uint16_t base_lo;
			uint8_t base_hi;
			uint8_t type;
			uint8_t limit_hi;
			uint8_t base_vhi;

		public:
			SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
				uint32_t Base();
                uint32_t Limit();
	} __attribute__((packed));

private:
	SegmentDescriptor nullSegmentSelector;
	SegmentDescriptor unusedSegmentSelector;
	SegmentDescriptor codeSegmentSelector;
	SegmentDescriptor dataSegmentSelector;
public:
	GlobalDescriptorTable();
	~GlobalDescriptorTable();

	uint16_t CodeSegmentSelector();
	uint16_t DataSegmentSelector();
};

#endif // GDT_H
