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

enum COLORS
{
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHTGRAY = 7,
  DARKGRAY = 8,
  LIGHTBLUE = 9,
  LIGHTGREEN = 10,
  LIGHTCYAN = 11,
  LIGHTRED = 12,
  LIGHTMAGENTA = 13,
  YELLOW = 14,
  WHITE = 15,
  BLINK = 128
};

enum CURSORTYPE
{
  _NOCURSOR,//     turns off the cursor
  _SOLIDCURSOR,//  solid block cursor
  _NORMALCURSOR // normal underscore cursor
};

extern struct text_info
{
  unsigned char attribute;      /* text attribute */
  unsigned char normattr;       /* normal attribute */
  int screenheight;   /* text screen's height */
  int screenwidth;    /* text screen's width */
  int curx;           /* x-coordinate in current window */
  int cury;           /* y-coordinate in current window */
} TEXT_INFO;

extern struct text_info_extended{
    int tabsize;
} TEXT_INFO_EXT;


void mputch(char);

void mcprintf(const char *);

void mclrscr(void);


#endif // MCONIO_H
