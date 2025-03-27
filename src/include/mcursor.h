/* mcursor.h

todo: add description

*/
#ifndef MCURSOR_H
#define MCURSOR_H

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);

void disable_cursor();

void update_cursor(int x, int y);

uint16_t get_cursor_position(void);

#endif // MCURSOR_H
