#ifndef BASICS_H
#define BASICS_H

// This is the x86's VGA textmode buffer. To display text, we write data to this memory location
extern volatile uint16_t* vga_buffer;
// By default, the VGA textmode buffer has a size of 80x25 characters
extern const int VGA_COLS;
extern const int VGA_ROWS;

// We start displaying text in the top-left of the screen (column = 0, row = 0)
extern int term_col;
extern int term_row;
extern uint8_t term_color;

// This function initiates the terminal by clearing it
void term_init();

// This function places a single character onto the screen
void term_putc(char c);

// This function prints an entire string onto the screen
void term_print(const char* str);

#endif // BASICS_H