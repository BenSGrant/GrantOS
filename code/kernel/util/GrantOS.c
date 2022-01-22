#include "GrantOS.h"

int currentCharPrintOffset = 0;

void charAt(char c, int offset) {
	/*
    	create a pointer to a character and point it to 
    	the first text cell of video memory (top left
    	of the screen) + 2 * offset which is the offset
    	from this position in supposed VRAM
    */
	char* video_memory = (char*) (0xb8000 + 2*offset);
	/*
		at the address pointed to by the video_memory variable, store
		the character 'X'
	*/
	*video_memory = c;
}

void print(char *s, int s_len) {
	for (int i = 0; i < s_len; i++) {
		charAt(s[i], currentCharPrintOffset++);
	}
}
