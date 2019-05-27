#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "console-vga-text.hxx"
#include "types.h"

extern "C"
{
    #include "string.h"
}

Terminal::Terminal(enum vgaColor fg=VGA_COLOR_LIGHT_GREY, 
                   enum vgaColor bg=VGA_COLOR_BLACK) :
    row(0), column(0), color(VgaEntryColor(fg, bg))
{
    if(!defaultTerminal) 
    {
        defaultTerminal = this;
        //default_terminal = static_cast<terminal_t>(this);
    }
    buffer = (uint16_t*) 0xB8000;
    Clear();
}

Terminal::~Terminal()
{
    //Clear();
}

void Terminal::Clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			buffer[index] = VgaEntry(' ', color);
		}
	}
}

Terminal* Terminal::GetDefaultTerminal()
{
    return defaultTerminal;
}

void Terminal::SetDefaultTerminal(Terminal& terminal)
{
    defaultTerminal = &terminal;
    //default_terminal = static_cast<terminal_t>(defaultTerminal);
}

void Terminal::SetColor(enum vgaColor fg, enum vgaColor bg)
{
    color = VgaEntryColor(fg, bg);
}

void Terminal::Scroll(int numLines)
{
	size_t y;
	for(y = 0; y < VGA_HEIGHT-numLines; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index_from = (y+1) * VGA_WIDTH + x;
			const size_t index_to = y * VGA_WIDTH + x;
			buffer[index_to] = buffer[index_from];
		}
	}
	for(;y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			buffer[index] = VgaEntry(' ', color);
		}
	}
}
 
void Terminal::PutEntryAt(char c, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	buffer[index] = VgaEntry(c, color);
}
 
void Terminal::PutChar(char c) 
{
	if(c != '\n')
	{
		PutEntryAt(c, column, row);
	}
	if (++column == VGA_WIDTH || c == '\n')
	{
		column = 0;
		if (++row == VGA_HEIGHT)
		{
			Scroll(1);
			row = VGA_HEIGHT-1;
		}
	}
}

void Terminal::Write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
	{
		PutChar(data[i]);
	}
}
 
void Terminal::WriteString(const char* str) 
{
	Write(str, strlen(str));
}

inline void Terminal::PrintF(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    
    VPrintF(fmt, args);

    va_end(args);
}

inline void Terminal::VPrintF(const char* fmt, va_list args)
{    
    size_t len = strlen(fmt);
    size_t beg = 0;
    size_t index = strfnd(fmt, '%', beg);
    Write(fmt, index);
    while(index+1 < len)
    {
        if(fmt[index+1] == '%')
        {
            Write(&fmt[index++],2);
        }
        else
        {
            const char* num;
            switch (fmt[++index])
            {
                case 'd':
                {
                    int32_t n = va_arg(args, int32_t);
                    num = i32tos(n, 10);
                    break;
                }
                case 'u':
                {
                    uint32_t n = va_arg(args, uint32_t);
                    num = u32tos(n, 10);
                    break;
                }
                case 'x':
                {
                    uint32_t n = va_arg(args, uint32_t);
                    num = u32tos(n, 16);
                    break;
                }
                case 's':
                {
                    num = va_arg(args,char*);
                    break;
                }
                default :
                {
                    static char buf[20] = {0};
                    buf[0] = '[';
                    buf[1] = fmt[index];
                    strcpy(&buf[2], ": unsupported] ");
                    num = buf;
                }
            }
            WriteString(num);
        }
        beg = index+1;
        index = MIN(len,strfnd(fmt, '%', beg));
        Write(&fmt[beg], index-beg);
    }
}

#ifdef __cplusplus
extern "C"
{
#endif
void printf(const char* fmt, ...)
{
    if(Terminal::GetDefaultTerminal())
    { 
        va_list args;
        va_start(args, fmt);
    
        Terminal::GetDefaultTerminal()->VPrintF(fmt, args);
   
        va_end(args);
    }
} 

void terminal_printf(terminal_t self, const char* fmt, ...)
{
    Terminal* typecast_ptr = static_cast<Terminal*>(self);
    va_list args;
    va_start(args, fmt);
    
    typecast_ptr->VPrintF(fmt, args);
    
    va_end(args);
}

terminal_t terminal_get_default() 
{
    return static_cast<terminal_t>(Terminal::GetDefaultTerminal());
}


terminal_t terminal_create(enum vgaColor fg, enum vgaColor bg)
{
    return new Terminal(fg, bg);
}

/*
void terminal_destroy(terminal_t void_ptr)
{
    Terminal* typecast_ptr = static_cast<Terminal*>(void_ptr);
    delete typecast_ptr;
}
*/

void terminal_set_color(terminal_t self, 
                        enum vgaColor fg,
                        enum vgaColor bg)
{
    Terminal* typecast_self = static_cast<Terminal*>(self);
    typecast_self->SetColor(fg,bg);
}

void terminal_putchar(terminal_t self, char c)
{
    Terminal* typecast_self = static_cast<Terminal*>(self);
    typecast_self->PutChar(c);
}

void terminal_write(terminal_t self, const char* data, size_t size)
{
    Terminal* typecast_self = static_cast<Terminal*>(self);
    typecast_self->Write(data, size);
}

void terminal_writestring(terminal_t self, const char* str)
{
    Terminal* typecast_self = static_cast<Terminal*>(self);
    typecast_self->WriteString(str);
}

#ifdef __cplusplus
}
#endif
