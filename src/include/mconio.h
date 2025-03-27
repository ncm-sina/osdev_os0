#ifndef MCONIO_H
#define MCONIO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void clrscr(void);
void sprintf(char *output, const char *fstring, ...); // puts result inside output instead of printing it
void cprintf(const char* fstring, ...); // Variadic with ANSI color support
void printf(const char* fstring, ...); // Variadic without ANSI color support
void set_textcolor(uint8_t fg, uint8_t bg);
uint8_t get_textcolor(void);
void set_text_fg_color(uint8_t fg);
uint8_t get_text_fg_color(void);
void set_text_bg_color(uint8_t bg);
uint8_t get_text_bg_color(void);
void gotoxy(uint8_t x, uint8_t y);

#endif