#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <mconio.h>

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

struct text_info
{
  unsigned char attribute;      /* text attribute */
  unsigned char normattr;       /* normal attribute */
  int screenheight;   /* text screen's height */
  int screenwidth;    /* text screen's width */
  int curx;           /* x-coordinate in current window */
  int cury;           /* y-coordinate in current window */
} TEXT_INFO = {
    0x0f,
    0x0f,
    25,
    80,
    0,
    0
};

struct text_info_extended{
    int tabsize;
} TEXT_INFO_EXT = {
    8
};

// This is the x86's VGA textmode buffer. To display text, we write data to this memory location
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
volatile size_t current_vga_index = 0;

void _calculate_current_vga_index(){
    current_vga_index = ((TEXT_INFO.screenwidth * (TEXT_INFO.cury)) + TEXT_INFO.curx); // Like before, calculate the buffer index
}

void _check_cursor_position()
{
    if(TEXT_INFO.curx >= TEXT_INFO.screenwidth){
        TEXT_INFO.curx = 0;
        TEXT_INFO.cury++;
        _calculate_current_vga_index();
    }
    if(TEXT_INFO.cury >= TEXT_INFO.screenheight){
        TEXT_INFO.cury=0;
        _calculate_current_vga_index();
    }
}

void _update_cursor()
{
    _calculate_current_vga_index();
}

void _handlebackslash()
{

}

void mputch(char ch)
{
    vga_buffer[current_vga_index] = ((uint16_t)TEXT_INFO.attribute << 8)  | ch;
    TEXT_INFO.curx++;
    current_vga_index++;
    _check_cursor_position();
    _update_cursor();
}

void mputch_at(char ch, int x, int y)
{
    const size_t index = ((TEXT_INFO.screenwidth * (y)) + x); // Like before, calculate the buffer index
    vga_buffer[index] = ((uint16_t)TEXT_INFO.attribute << 8)  | ch;
}

void mcprintf(const char *fstring)
{
    #define MAX_STRING_LENGTH 2000
    char tmpbuffer[10];
    int tmpbufferlen = 0;
    // char tmpattribute = 0;
    bool errorFlag = false;
    for(int i=0; fstring[i] != 0 && i<MAX_STRING_LENGTH; i++){
        errorFlag=false;
        if(
            (fstring[i]>= 32 /*&& fstring[i]<=255*/) && fstring[i] != 127 // if its printable character
        ){
            mputch(fstring[i]);
            continue;
        }

        switch(fstring[i])
        {
        case '\n':
            TEXT_INFO.curx=0;
            TEXT_INFO.cury++;
            _check_cursor_position();
            _update_cursor();
            break;
        case '\t':
            TEXT_INFO.curx += TEXT_INFO_EXT.tabsize - (TEXT_INFO.curx % TEXT_INFO_EXT.tabsize);
            _check_cursor_position();
            _update_cursor();
            break;
        case '\r': // ignore
            break;
        case '\033':
//            _handlebackslash();
            if( // check if its a color change CSI
                (
                    fstring[i+1] == '['
                )
                //  ||
                // (
                //     fstring[i+1] == '['
                // )
            ){
                i+=2; // we skip 2 characters to get to numbers 1:'\033' 2:'[' -> XX;YY;ZZm
                while( fstring[i] != 'm' && fstring[i] != 0 && !errorFlag ){ // m means end of the color change CSI
                    tmpbufferlen = 0;
                    while(fstring[i] != ';' && fstring[i] != 'm' && fstring[i] != 0 && !errorFlag){
                        if(fstring[i] >= '0' && fstring[i]<='9'){
                            tmpbuffer[tmpbufferlen]=fstring[i];
                            tmpbufferlen++;
                        }else{
                            errorFlag = true;
                        }
                        i++;
                    }
                    tmpbuffer[tmpbufferlen] = 0;
                    // TEXT_INFO.attribute = 0x21;
                    // mcprintf(tmpbuffer);
                    // TEXT_INFO.attribute = 0x31;
                    // mcprintf(tmpbuffer);
                    // TEXT_INFO.attribute = TEXT_INFO.normattr;
                    // mcprintf(tmpbuffer);
                    if(tmpbuffer[0] == '0'){
                        TEXT_INFO.attribute = TEXT_INFO.normattr; // reset to default
                    }else if(tmpbuffer[0] == '3'){
                        TEXT_INFO.attribute = TEXT_INFO.attribute & 0xf0; // we get rid of attribute's low bit
                        TEXT_INFO.attribute = TEXT_INFO.attribute | (tmpbuffer[1] - '0');   
                    }else if(tmpbuffer[0] == '9'){
                        TEXT_INFO.attribute &= 0xf0; // we get rid of attribute's low bit
                        TEXT_INFO.attribute |= (tmpbuffer[1] - '0' + 8);
                    }else if(tmpbuffer[0] == '4'){
                        TEXT_INFO.attribute = TEXT_INFO.attribute & 0x0f; // we get rid of attribute's low bit
                        TEXT_INFO.attribute = TEXT_INFO.attribute | ((tmpbuffer[1] - '0') << 4);
                    }else if(tmpbuffer[0] == '1' && tmpbuffer[1] == '0'){
                        TEXT_INFO.attribute = TEXT_INFO.attribute & 0x0f; // we get rid of attribute's low bit
                        TEXT_INFO.attribute = TEXT_INFO.attribute | ((tmpbuffer[2] - '0' + 8) << 4);
                    }
                    if(fstring[i] == 0 || fstring[i] == 'm'){
                        break;
                    }
                    i++;
                }
            }
            break;
        // default: // ignore the rest for now

        }
    }
}


void mclrscr(void)
{
    const uint16_t cleanerChar = TEXT_INFO.attribute << 8 | ' ';
    for(int i=0;i<TEXT_INFO.screenheight * TEXT_INFO.screenwidth;i++){
        vga_buffer[i] = cleanerChar;
    }
}