#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

bool isdigit(const char c);

size_t strlen(const char* str);

void strrev(char* str);

bool strcmp(const char* S, const char* T);

bool strncmp(const char* S, const char* T, size_t nchars);

size_t strfnd(const char* str, const char c, size_t pos);

char* strcpy(char* dst, const char* src);

char* strncpy(char* dst, const char* src, size_t nchars);

const char* u32tos(uint32_t num, int base);

const char* i32tos(int32_t num, int base);


