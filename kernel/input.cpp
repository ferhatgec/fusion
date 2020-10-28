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

#include "../include/kernel.h"
#include "../include/io/input.h"
#include "../include/io/layout.h"
#include "../include/vga/vga.h"

void printf(char*, unsigned char, unsigned char);
void write_string(int colour, const char *string);
void show_buffer();

inline unsigned char inb(unsigned short port);
inline void outb(unsigned short port, unsigned char value);

string
KeyboardInput::GetInput() {
    char buff;
    string buffstr;
    
    uint8_t i = 0;
    uint8_t reading = 1;
    
    while(reading) {
        if(inb(0x64) & 0x1) {
            switch(inb(0x60)) { 
            	/* TODO:
            		Add print char function with 
            			color options. 
        		*/
        		
        		case 2:
                	printf("1", GRAY_COLOR, 0);
                	buffstr[i] = '1';
                	i++;
                	break;
        		case 3:
					printf("2", GRAY_COLOR, 0);
            	    buffstr[i] = '2';
            	    i++;
            	    break;
        		case 4:
                	printf("3", GRAY_COLOR, 0);
                	buffstr[i] = '3';
                	i++;
                	break;
        		case 5:
                	printf("4", GRAY_COLOR, 0);
                	buffstr[i] = '4';
                	i++;
                	break;
        		case 6:
                	printf("5", GRAY_COLOR, 0);
                	buffstr[i] = '5';
                	i++;
                	break;
        		case 7:
                	printf("6", GRAY_COLOR, 0);
                	buffstr[i] = '6';
                	i++;
                	break;
        		case 8:
                	printf("7", GRAY_COLOR, 0);
                	buffstr[i] = '7';
                	i++;
                	break;
        		case 9:	
                	printf("8", GRAY_COLOR, 0);
                	buffstr[i] = '8';
                	i++;
                	break;
        		case 10:
                	printf("9", GRAY_COLOR, 0);
                	buffstr[i] = '9';
                	i++;
                	break;
        		case 11:
                	printf("0", GRAY_COLOR, 0);
                	buffstr[i] = '0';
                	i++;
                	break;
        		case 12:	
                	printf("-", GRAY_COLOR, 0);
                	buffstr[i] = '-';
                	i++;
                	break;
        		case 13:	
                	printf("=", GRAY_COLOR, 0);
                	buffstr[i] = '=';
                	i++;
                	break;
        		case 14:	
                	printf("\b", GRAY_COLOR, 0);
                	i--;
                	
                	if(i < 0) {
                		i = 0;
                	}
                
                	buffstr[i+1] = 0;
                	buffstr[i] = 0;
                	break;
        		case 16:
                	printf("q", GRAY_COLOR, 0);
                	buffstr[i] = 'q';
                	i++;
                	break;
        		case 17:
                	printf("w", GRAY_COLOR, 0);
                	buffstr[i] = 'w';
                	i++;
                	break;
        		case 18:
                	printf("e", GRAY_COLOR, 0);
                	buffstr[i] = 'e';
                	i++;
                	break;
        		case 19:
                	printf("r", GRAY_COLOR, 0);
                	buffstr[i] = 'r';
                	i++;
                	break;
        		case 20:
        			printf("t", GRAY_COLOR, 0);
                	buffstr[i] = 't';
                	i++;
                	break;
	        	case 21:
    	            printf("y", GRAY_COLOR, 0);
    	            buffstr[i] = 'y';
    	            i++;
    	            break;
    		    case 22:
    	            printf("u", GRAY_COLOR, 0);
    	            buffstr[i] = 'u';
    	            i++;
    	            break;
    		    case 23:
    		    	printf("i", GRAY_COLOR, 0);
    	            buffstr[i] = 'i';
    	            i++;
    	            break;
    		    case 24:
    	            printf("o", GRAY_COLOR, 0);
    	            buffstr[i] = 'o';
    	            i++;
    	            break;
    		    case 25:
					printf("p", GRAY_COLOR, 0);
    	            buffstr[i] = 'p';
    	            i++;
    	            break;
    		    case 26:
					printf("[", GRAY_COLOR, 0);
    	            buffstr[i] = '[';
    	            i++;
    	            break;
    		    case 27:
					printf("]", GRAY_COLOR, 0);
        	        buffstr[i] = ']';
        	        i++;
        	        break;
        		case 28:
        			printf("\n", GRAY_COLOR, 0);
					i++;
        	        reading = 0;
        	        break;
        		case 30:
                	printf("a", GRAY_COLOR, 0);
                	buffstr[i] = 'a';
                	i++;
                	break;
        		case 31:
                	printf("s", GRAY_COLOR, 0);
                	buffstr[i] = 's';
                	i++;
                	break;
        		case 32:	
                	printf("d", GRAY_COLOR, 0);
                	buffstr[i] = 'd';
                	i++;
                	break;
        		case 33:
                	printf("f", GRAY_COLOR, 0);
                	buffstr[i] = 'f';
                	i++;
                	break;
        		case 34:
                	printf("g", GRAY_COLOR, 0);
                	buffstr[i] = 'g';
                	i++;
                	break;
        		case 35:
                	printf("h", GRAY_COLOR, 0);
                	buffstr[i] = 'h';
                	i++;
                	break;
        		case 36:
                	printf("j", GRAY_COLOR, 0);
                	buffstr[i] = 'j';
                	i++;
                	break;
        		case 37:
                	printf("k", GRAY_COLOR, 0);
                	buffstr[i] = 'k';
                	i++;
                	break;
        		case 38:
                	printf("l", GRAY_COLOR, 0);
                	buffstr[i] = 'l';
                	i++;
                	break;
        		case 39:
					printf(";", GRAY_COLOR, 0);
                	buffstr[i] = ';';
                	i++;
                	break;
        		case 40:	
                	printf("'", GRAY_COLOR, 0);
                	buffstr[i] = (char)44;
                	i++;
                	break;
        		case 41:	
                	printf("`", GRAY_COLOR, 0);
                	buffstr[i] = (char)44;
                	i++;
                	break;
        		case 44:
                	printf("z", GRAY_COLOR, 0);
                	buffstr[i] = 'z';
                	i++;
                	break;
        		case 45:
                	printf("x", GRAY_COLOR, 0);
                	buffstr[i] = 'x';
                	i++;
                	break;
        		case 46:
            	    printf("c", GRAY_COLOR, 0);
            	    buffstr[i] = 'c';
            	    i++;
            	    break;
        		case 47:
                	printf("v", GRAY_COLOR, 0);
                	buffstr[i] = 'v';
                	i++;
                	break;                
        		case 48:
                	printf("b", GRAY_COLOR, 0);
                	buffstr[i] = 'b';
                	i++;
                	break;               
        		case 49:	
                	printf("n", GRAY_COLOR, 0);
                	buffstr[i] = 'n';
                	i++;
                	break;                
        		case 50:
                	printf("m", GRAY_COLOR, 0);
                	buffstr[i] = 'm';
                	i++;
                	break;               
        		case 51:
					printf(",", GRAY_COLOR, 0);
                	buffstr[i] = ',';
                	i++;
                	break;                
        		case 52:
					printf(".", GRAY_COLOR, 0);
                	buffstr[i] = '.';
                	i++;
                	break;            
        		case 53:
                	printf("/", GRAY_COLOR, 0);
                	buffstr[i] = '/';
                	i++;
                	break;            
        		case 54:
					printf(".", GRAY_COLOR, 0);
                	buffstr[i] = '.';
                	i++;
                	break;            
        		case 55:
                	printf("/", GRAY_COLOR, 0);
                	buffstr[i] = '/';
                	i++;
                	break;                       
        		case 57:
            	    printf(" ", GRAY_COLOR, 0);
            	    buffstr[i] = ' ';
            	    i++;
            	    break;
            }
        }	
    }

	/* i++ from enter key signal */
    buffstr[i - 1] = 0;                
 
    return buffstr;
}

string
KeyboardInput::GetPassInput() {
    char buff;
    string buffstr;
    
    uint8_t i = 0;
    uint8_t reading = 1;
    
    while(reading) {
        if(inb(0x64) & 0x1) {
            switch(inb(0x60)) { 
            	/* TODO:
            		Add print char function with 
            			color options. 
        		*/
        		
        		case 2:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '1';
                	i++;
                	break;
        		case 3:
					printf("2", GRAY_COLOR, 0);
            	    buffstr[i] = '2';
            	    i++;
            	    break;
        		case 4:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '3';
                	i++;
                	break;
        		case 5:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '4';
                	i++;
                	break;
        		case 6:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '5';
                	i++;
                	break;
        		case 7:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '6';
                	i++;
                	break;
        		case 8:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '7';
                	i++;
                	break;
        		case 9:	
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '8';
                	i++;
                	break;
        		case 10:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '9';
                	i++;
                	break;
        		case 11:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '0';
                	i++;
                	break;
        		case 12:	
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '-';
                	i++;
                	break;
        		case 13:	
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '=';
                	i++;
                	break;
        		case 14:	
                	printf("\b", GRAY_COLOR, 0);
                	i--;
                	
                	if(i < 0) {
                		i = 0;
                	}
                
                	buffstr[i+1] = 0;
                	buffstr[i] = 0;
                	break;
        		case 16:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'q';
                	i++;
                	break;
        		case 17:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'w';
                	i++;
                	break;
        		case 18:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'e';
                	i++;
                	break;
        		case 19:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'r';
                	i++;
                	break;
        		case 20:
        			printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 't';
                	i++;
                	break;
	        	case 21:
    	            printf("*", GRAY_COLOR, 0);
    	            buffstr[i] = 'y';
    	            i++;
    	            break;
    		    case 22:
    	            printf("*", GRAY_COLOR, 0);
    	            buffstr[i] = 'u';
    	            i++;
    	            break;
    		    case 23:
    		    	printf("*", GRAY_COLOR, 0);
    	            buffstr[i] = 'i';
    	            i++;
    	            break;
    		    case 24:
    	            printf("*", GRAY_COLOR, 0);
    	            buffstr[i] = 'o';
    	            i++;
    	            break;
    		    case 25:
					printf("*", GRAY_COLOR, 0);
    	            buffstr[i] = 'p';
    	            i++;
    	            break;
    		    case 26:
					printf("*", GRAY_COLOR, 0);
    	            buffstr[i] = '[';
    	            i++;
    	            break;
    		    case 27:
					printf("*", GRAY_COLOR, 0);
        	        buffstr[i] = ']';
        	        i++;
        	        break;
        		case 28:
        			printf("\n", GRAY_COLOR, 0);
					i++;
        	        reading = 0;
        	        break;
        		case 30:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'a';
                	i++;
                	break;
        		case 31:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 's';
                	i++;
                	break;
        		case 32:	
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'd';
                	i++;
                	break;
        		case 33:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'f';
                	i++;
                	break;
        		case 34:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'g';
                	i++;
                	break;
        		case 35:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'h';
                	i++;
                	break;
        		case 36:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'j';
                	i++;
                	break;
        		case 37:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'k';
                	i++;
                	break;
        		case 38:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'l';
                	i++;
                	break;
        		case 39:
					printf("*", GRAY_COLOR, 0);
                	buffstr[i] = ';';
                	i++;
                	break;
        		case 40:	
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = (char)44;
                	i++;
                	break;
        		case 41:	
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = (char)44;
                	i++;
                	break;
        		case 44:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'z';
                	i++;
                	break;
        		case 45:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'x';
                	i++;
                	break;
        		case 46:
            	    printf("*", GRAY_COLOR, 0);
            	    buffstr[i] = 'c';
            	    i++;
            	    break;
        		case 47:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'v';
                	i++;
                	break;                
        		case 48:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'b';
                	i++;
                	break;               
        		case 49:	
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'n';
                	i++;
                	break;                
        		case 50:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = 'm';
                	i++;
                	break;               
        		case 51:
					printf("*", GRAY_COLOR, 0);
                	buffstr[i] = ',';
                	i++;
                	break;                
        		case 52:
					printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '.';
                	i++;
                	break;            
        		case 53:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '/';
                	i++;
                	break;            
        		case 54:
					printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '.';
                	i++;
                	break;            
        		case 55:
                	printf("*", GRAY_COLOR, 0);
                	buffstr[i] = '/';
                	i++;
                	break;                       
        		case 57:
            	    printf("*", GRAY_COLOR, 0);
            	    buffstr[i] = ' ';
            	    i++;
            	    break;
            }
        }	
    }

	/* i++ from enter key signal */
    buffstr[i - 1] = 0;                
 
    return buffstr;
}
