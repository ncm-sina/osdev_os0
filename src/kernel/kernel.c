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

#include "mconio.h"
#include "mport.c"
#include "vga_basic.h"

// Static function to hide the cursor using port I/O
static void _hide_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20); // Disable cursor
}

// Kernel initialization
static void kernel_init(void) {
    _hide_cursor();
}

// Kernel main function
void kernel_main(void) {
    kernel_init();
    clrscr();

    // Basic variables for testing
    const char *name = "Dave";
    int num = 42;
    char c = '!';
    int negative = -123;

    // Example 1: Simple cprintf with ANSI colors
    cprintf("Hello, \033[32;40m%s\033[0m! Num: %d%%\n", name, num);
    
    // Example 2: printf with tab and percentage
    printf("Tab test:\tThis is tabbed, %s. Percent: %d%%\n", name, num);

    // Example 3: More complex cprintf with multiple colors and formats
    cprintf("User: \033[31m%s\033[0m, Score: \033[33m%d\033[0m, Char: %c\n", name, num, c);

    // Example 4: Negative number and gotoxy
    gotoxy(0, 3);
    printf("Negative number: %d\n", negative);

    // Example 5: Using sprintf to build a string
    char test_buffer[64];
    sprintf(test_buffer, "Combined: %s scored %d points %c", name, num, c);
    gotoxy(0, 4);
    printf("Sprintf result: %s\n", test_buffer);

    // Example 6: Changing text color manually
    set_textcolor(VGA_COLOR_CYAN, VGA_COLOR_DARK_GREY);
    printf("Cyan on dark grey: %d%%\n", num);
    _vgab_reset_textcolor(); // Reset to default

    // Example 7: Tab size adjustment
    _vgab_set_tabsize(4);
    printf("Smaller tab:\t%d\n", num);
    _vgab_set_tabsize(8); // Reset to default

    // // Example 8: Multiple lines with scrolling
    // for (int i = 0; i < 30; i++) {
    //     printf("Line %d\n", i);
    // }
}