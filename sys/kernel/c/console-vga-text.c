#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "console-vga-text.h"
inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
	{
		len++;
	}
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;
 
void terminal_initialize(enum vga_color fg, enum vga_color bg) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(fg, bg);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
static void terminal_scroll(int num_lines)
{
	size_t y;
	for(y = 0; y < VGA_HEIGHT-num_lines; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index_from = (y+1) * VGA_WIDTH + x;
			const size_t index_to = y * VGA_WIDTH + x;
			terminal_buffer[index_to] = terminal_buffer[index_from];
		}
	}
	for(;y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	if(c != '\n')
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	}
	if (++terminal_column == VGA_WIDTH || c == '\n')
	{
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_scroll(1);
			terminal_row = VGA_HEIGHT-1;
		}
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
	{
		terminal_putchar(data[i]);
	}
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
	
}
 
