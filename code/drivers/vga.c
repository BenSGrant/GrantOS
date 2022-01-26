#include "vga.h"

unsigned port_byte_in(unsigned short port) {
	/*
		we map the C variable port into the dx CPU register,
		execute in al, dx, and then store the value of the al
		register into the C variable result.
	*/
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
	/*
		executes out dx, al, mapping the port to dx and the
		data to al.
	*/
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void set_cursor(int offset) {
	offset /= 2;
	port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
	port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8)); // right bit shift (moves each binary bit over to the right)
	port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
	port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
	port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
	int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
	port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
	offset += port_byte_in(VGA_DATA_REGISTER);
	return offset * 2;
}

void charAt(char c, int offset) {
	offset *= 2; // there are 2 bytes of video memory per text cell as explained in a bit
	/*
	    	create a pointer to a character and point it to
	    	the first text cell of video memory (top left
	    	of the screen)
    	*/
	char* video_memory = (unsigned char*) VID_MEM;
	/*
		at the address pointed to by the video_memory variable, store
		the character in variable c.

		there are 2 bytes per text cell in video memory (one for the
		character and one for the colour)
	*/
	video_memory[offset] = c;
	video_memory[offset+1] = WHITE_ON_BLACK;
}

void print(char *s) {
	int offset = get_cursor();
	int i = 0;
	while (s[i] != 0) {
		charAt(s[i], offset);
		i++;
		offset +=1;
	}
	set_cursor(offset);
}
