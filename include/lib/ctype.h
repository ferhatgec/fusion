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

#ifndef CTYPE_H
#define CTYPE_H
 
#define CT_UP	0x01	// Uppercase 
#define CT_LOW	0x02	// lowercase 
#define CT_DIG	0x04	// Digit */
#define CT_CTL	0x08	// Control */
#define CT_PUN	0x10	// Punctuation */
#define CT_WHT	0x20	// Whitespace (space/cr/lf/tab) */
#define CT_HEX	0x40	// Hex digit 
#define CT_SP	0x80	// Hardspace (0x20) 

#endif // CTYPE_H
