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

#include <mconio.h>



// This is our kernel's main function
void kernel_main()
{
	// We're here! Let's initiate the terminal and display a message to show we got here.
	

	mclrscr();

	// Display some messages
	mcprintf("He\033[30mllo,World!\033[0m\n");
	mcprintf("He\033[31mllo,World!\033[0m\n");
	mcprintf("He\033[32mllo,World!\033[0m\n");
	mcprintf("He\033[33mllo,World!\033[0m\n");
	mcprintf("He\033[34mllo,World!\033[0m\n");
	mcprintf("He\033[35mllo,World!\033[0m\n");
	mcprintf("He\033[36mllo,World!\033[0m\n");
	mcprintf("He\033[37mllo,World!\033[0m\n");
	mcprintf("He\033[40mllo,World!\033[0m\n");
	mcprintf("He\033[41mllo,World!\033[0m\n");
	mcprintf("He\033[42mllo,World!\033[0m\n");
	mcprintf("He\033[43mllo,World!\033[0m\n");
	mcprintf("He\033[44mllo,World!\033[0m\n");
	mcprintf("He\033[45mllo,World!\033[0m\n");
	mcprintf("He\033[46mllo,World!\033[0m\n");
	mcprintf("He\033[47mllo,World!\033[0m\n");

	

	// // Display some messages
	// mcprintf("Hello, World2!\n");
	// mcprintf("Welcome to the kernel.\n");
}