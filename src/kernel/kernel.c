// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

#include "basics.h"


// This is our kernel's main function
void kernel_main()
{
	// We're here! Let's initiate the terminal and display a message to show we got here.
	
	// Initiate terminal
	term_init();

	// Display some messages
	term_print("Hello, World!\n");
	term_print("Welcome to the kernel.\n");
}