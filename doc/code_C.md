# CODE HELP

## multiple declaration error:
> try to make sure that a variable declared in a header is of type extern and  
> is actually defined in the .c file  
> EXAMPLE:  

	// don't do this:
	
	// file.h
	int x = 0;
	
	// file.c
	x+=2;

	// instead do this:

	// file.h
	extern int x;

	// file.c
	int x = 0;
	x+=2;
