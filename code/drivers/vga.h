// SYSTEM VARIABLES

#define VGA_CTRL_REGISTER 0x3d4 // 980
#define VGA_DATA_REGISTER 0x3d5 // 981
#define VGA_OFFSET_LOW 0x0f     // 15
#define VGA_OFFSET_HIGH 0x0e    // 14
#define VID_MEM 0x8000		// top left video memory cell
#define SCR_MAX_ROWS 0x19	// 25
#define SCR_MAX_COLS 0x50	// 80
#define WHITE_ON_BLACK 0x0f	// 15 - colour data for vid mem


// SYSTEM FUNCTIONS

extern unsigned char port_byte_in(unsigned short port);
extern void port_byte_out(unsigned short port, unsigned char data);

extern void set_cursor(int offset);
extern int get_cursor();

// put a character onto the screen at the position given by the offset (from the top left of the screen)
extern void charAt(char c, int offset);
// prints a char array (string) to the screen using iteration
extern void print(char *s);
