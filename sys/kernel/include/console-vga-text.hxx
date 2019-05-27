/* Hardware text mode color constants. */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
extern "C" {
    #include "string.h"
}

enum vgaColor {
	ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssdfdddddddddd
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

class Terminal
{
private:
    static constexpr size_t VGA_WIDTH = 80;
    static constexpr size_t VGA_HEIGHT = 25;
    static inline constexpr uint8_t VgaEntryColor(enum vgaColor fg, enum vgaColor bg) 
    {
	    return fg | bg << 4;
    }
    static inline constexpr uint16_t VgaEntry(unsigned char uc, uint8_t color) 
    {
	    return (uint16_t) uc | (uint16_t) color << 8;
    }
    inline static Terminal* defaultTerminal = nullptr;
    size_t row;
    size_t column;
    
    uint8_t color;
    uint16_t* buffer;
    void Scroll(int numLines);
    void PutEntryAt(char c, size_t x, size_t y);
    
public:
    Terminal(enum vgaColor fg, enum vgaColor bg);
    ~Terminal();
    void Clear();
    void SetColor(enum vgaColor fg, enum vgaColor bg);
    void PutChar(char c);
    void Write(const char* data, size_t size);
    void WriteString(const char* str);
    void PrintF(const char* fmt, ...);
    void VPrintF(const char* fmt, va_list args);
    static Terminal* GetDefaultTerminal();
    static void SetDefaultTerminal(Terminal& terminal);
};

#ifdef __cplusplus
extern "C"
{
#endif
typedef void* terminal_t;
terminal_t terminal_create(enum vgaColor fg, enum vgaColor bg);

void       terminal_destroy(terminal_t);

void       terminal_set_color(terminal_t self, 
                              enum vgaColor fg,
                              enum vgaColor bg);

void       terminal_putchar(terminal_t self, char c); 

void       terminal_write(terminal_t self, const char* data, size_t size);

void       terminal_writestring(terminal_t self, const char* str);

terminal_t terminal_get_default();

void       terminal_printf(terminal_t self, const char* fmt, ...);

void       printf(const char* fmt, ...);


#ifdef __cplusplus
}
#endif




