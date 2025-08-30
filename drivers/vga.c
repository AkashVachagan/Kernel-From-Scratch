#include "stdint.h"
#include "vga.h"
#include "colors.h"

#define VGA_ADDRESS 0xB8000

static volatile uint8_t *video = (volatile uint8_t *)VGA_ADDRESS;
static int cursor_row = 0;
static int cursor_col = 0;

static inline uint8_t vga_color(uint8_t fg, uint8_t bg){
    return (bg << 4) | (fg & 0x0F);
}

void put_char(char c, int x, int y, uint8_t color){
    int pos = y * 80 + x;
    video[2*pos] = c;
    video[2*pos + 1] = color;
}

void clear_screen(void){
    for (int i = 0; i < 80*25; i++){
        put_char(' ', i % 80, i / 80, vga_color(BLACK, BLACK));
    }
    cursor_row = 0;
    cursor_col = 0;
}

void scroll_screen(void){
    for (int i = 1; i < 25; i++){ 
        for (int j = 0; j < 80; j++){
            int pos = i*80 + j;
            uint8_t val = video[2*pos];
            uint8_t col = video[2*pos + 1];
            put_char(val, j, i-1, col);
        }
    }
    for (int j = 0; j < 80; j++){
        put_char(' ', j, 24, vga_color(BLACK, BLACK));
    }
}

void kprint_color(const char* str, uint8_t fg){
    uint8_t color = vga_color(fg, BLACK); 
    while (*str){
        if (*str == '\n'){
            cursor_row++;
            cursor_col = 0;
            if (cursor_row >= 25){
                scroll_screen();
                cursor_row = 24;
            }
        } else {
            put_char(*str, cursor_col, cursor_row, color);
            cursor_col++;
            if (cursor_col >= 80){
                cursor_col = 0;
                cursor_row++;
                if (cursor_row >= 25){
                    scroll_screen();
                    cursor_row = 24;
                }
            }
        }
        str++;
    }
}

void kprint(const char* str){
    kprint_color(str, WHITE);
}

void kprint_color_bg(const char* str, uint8_t fg, uint8_t bg){
    uint8_t color = vga_color(fg, bg);
    while (*str){
        if (*str == '\n'){
            cursor_row++;
            cursor_col = 0;
            if (cursor_row >= 25){
                scroll_screen();
                cursor_row = 24;
            }
        } else {
            put_char(*str, cursor_col, cursor_row, color);
            cursor_col++;
            if (cursor_col >= 80){
                cursor_col = 0;
                cursor_row++;
                if (cursor_row >= 25){
                    scroll_screen();
                    cursor_row = 24;
                }
            }
        }
        str++;
    }
}
