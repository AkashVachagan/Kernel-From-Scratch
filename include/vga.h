#ifndef VGA_H
#define VGA_H

#include "stdint.h"

void kprint(const char* str);

void kprint_color(const char* str, uint8_t fg);

void clear_screen(void);

void scroll_screen(void);

void put_char(char c, int x, int y, uint8_t color);

void kprint_color_bg(const char* str, uint8_t fg, uint8_t bg);

#endif 

