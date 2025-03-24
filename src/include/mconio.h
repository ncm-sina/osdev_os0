/* mconio.h

mkbhit	Determines if a keyboard key was pressed as well
mcgets	Reads a string directly from the console
mcscanf	Reads formatted values directly from the console
mputch	Writes a character directly to the console
mcputs	Writes a string directly to the console
mcprintf	Formats values and writes them directly to the console
mclrscr	Clears the screen
mgetch	Get char entry from the console
mgetche	Get char entry from the console with echo

*/
#ifndef MCONIO_H
#define MCONIO_H

void mputch(char);
void mcprintf(const char *);
void mclrscr(void);


#endif
