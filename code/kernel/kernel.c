void charAt(char c, int x){
	/*
     create a pointer to a character and point it to 
     the first text cell of video memory (top left
     of the screen) + 2 * x which is the offset from this position
    */
   char* video_memory = (char*) (0xb8000 + 2*x);
   /*
    at the address pointed to by the video_memory variable, store
    the character 'X'
   */
   *video_memory = c;
}









void main() {

	char msg[22] = "Welcome to GrantOS 0.1";
	char buf[4] = "    ";
	
	int charsPrinted = 0;
    for (int i = 0; i < 22; i++) {
    	charAt(msg[i], i);
    	charsPrinted++;
    }
    
    for (int i = 0; i < 4; i++) {
    	charAt(buf[i], charsPrinted);
    	charsPrinted++;
    }
}

