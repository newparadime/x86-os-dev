#include "types.h"
#include "string.h"

bool isdigit(const char c)
{
    return (c >= '0' && c <= '9');
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

void strrev(char* str)
{
    const size_t len = strlen(str);
    for(size_t i = 0; i < len; i++)
    {
        const char c = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = c;
    }
}

bool strcmp(const char* S, const char* T)
{
    size_t index = 0;
    while(S[index] && T[index] && S[index] == T[index]) index++;
    return !(!S[index] && !T[index]);
}

bool strncmp(const char* S, const char* T, size_t nchars)
{
    size_t index = 0;
    while(index < nchars && S[index] && T[index] && S[index] == T[index]) index++;
    return !((!S[index] && !T[index]) || (index == nchars && S[nchars-1] == T[nchars-1]));
}

size_t strfnd(const char* str, const char c, size_t pos)
{
    size_t len = strlen(str);
    while(pos < len && str[pos] != c) pos++;
    return pos;
}

char* strcpy(char* dst, const char* src)
{
    size_t index = 0;
    while(src[index])
    {
        dst[index] = src[index];
        index++;
    }
    dst[index] = '\0';
    return dst;
}

char* strncpy(char* dst, const char* src, size_t nchars)
{
    size_t index = 0;
    while(index < nchars && src[index])
    {
        dst[index] = src[index];
        index++;
    }
    if(index < nchars) 
    {
        dst[index] = '\0';
    }
    return dst;
}
#define LEN 12
#define NUM_BUFS 5
const char* u32tos(uint32_t num, int base)
{
    static char digits[NUM_BUFS][LEN+1];
    static size_t buf_i = 0;
    
    buf_i = (buf_i+1)%NUM_BUFS;
    digits[buf_i][LEN] = '\0';
    
    size_t i;
    for(i = LEN-1; num > 0; i--)
    {
        const int digit = num % base;
        if(digit >= 10)
        {
            digits[buf_i][i] = (digit-10)+'a';
        }
        else
        {
            digits[buf_i][i] = digit + '0';
        }
        num /= base;
    }
    if(i == LEN-1)
    {
        digits[buf_i][i] = '0';
    }
    return &digits[buf_i][i];
}

const char* i32tos(int32_t num, int base)
{
    static char digits[NUM_BUFS][LEN+1];
    static size_t buf_i = 0;

    buf_i = (buf_i+1)%NUM_BUFS;
    digits[buf_i][LEN] = '\0';

    size_t i = 0;
    if(num < 0)
    {
        digits[buf_i][i++] = '-';
        num *= -1;
    }

    strcpy(&digits[buf_i][i], u32tos(num, base));

    return digits[buf_i];
}






