//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_CONSOLE_H
#define TRTK_CONSOLE_H

#define CONSOLE_WIDTH   80
#define CONSOLE_HEIGHT  25
#define CONSOLE_MEMORY  0xB8000
#define CONSOLE_TAB_SIZE  4

#include <stdint.h>

void clear_screen();
void move_cursor();
void scroll();
void print_char(char c);
void print_string(const char *str);
void printf(const char *fmt, ...);

#endif //TRTK_CONSOLE_H
