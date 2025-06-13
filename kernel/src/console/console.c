//
// Created by Marco on 13/06/2025.
//

#include "console.h"
#include <stdarg.h>
#include "../io/io.h"

static uint16_t *const video_buffer = (uint16_t *) CONSOLE_MEMORY;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static uint8_t color = 0x07; // bianco su nero

void clear_screen() {
    for (int i = 0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT; i++)
        video_buffer[i] = ((uint16_t) color << 8) | ' ';
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void move_cursor() {
    uint16_t pos = cursor_y * CONSOLE_WIDTH + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, (pos >> 8) & 0xFF);
    outb(0x3D4, 15);
    outb(0x3D5, pos & 0xFF);
}

void scroll() {
    if (cursor_y >= CONSOLE_HEIGHT) {
        for (int y = 1; y < CONSOLE_HEIGHT; y++)
            for (int x = 0; x < CONSOLE_WIDTH; x++)
                video_buffer[(y - 1) * CONSOLE_WIDTH + x] = video_buffer[y * CONSOLE_WIDTH + x];
        for (int x = 0; x < CONSOLE_WIDTH; x++)
            video_buffer[(CONSOLE_HEIGHT - 1) * CONSOLE_WIDTH + x] = ((uint16_t) color << 8) | ' ';
        cursor_y = CONSOLE_HEIGHT - 1;
    }
}

void print_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\t') {
        cursor_x = (cursor_x + CONSOLE_TAB_SIZE) & ~(CONSOLE_TAB_SIZE - 1);
        if (cursor_x >= CONSOLE_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    } else {
        video_buffer[cursor_y * CONSOLE_WIDTH + cursor_x] = ((uint16_t) color << 8) | c;
        cursor_x++;
        if (cursor_x >= CONSOLE_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    scroll();
    move_cursor();
}

void print_string(const char *str) {
    while (*str)
        print_char(*str++);
}

static void print_uint32(uint32_t value, int base, int uppercase) {
    char buffer[33];
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int i = 0;

    if (value == 0) {
        print_char('0');
        return;
    }

    while (value > 0) {
        buffer[i++] = digits[value % base];
        value /= base;
    }

    while (i-- > 0)
        print_char(buffer[i]);
}

static void print_int32(int32_t value) {
    if (value < 0) {
        print_char('-');
        uint32_t abs_value = (uint32_t)(-(value + 1)) + 1;
        print_uint32(abs_value, 10, 0);
    } else {
        print_uint32((uint32_t)value, 10, 0);
    }
}

#define EXTRACT_MODIFIER(fmt, pos) ({      \
    int res = 0;                           \
    switch (fmt[pos]) {                    \
        case 'h': res = (fmt[pos + 1] == 'h') ? 1 : 2; break; \
        case 'l': res = (fmt[pos + 1] == 'l') ? 3 : 4; break; \
        default: res = 0;                  \
    } res; })

void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%') {
            i++;
            int mod = EXTRACT_MODIFIER(fmt, i);
            if (mod == 1 || mod == 3) i += 2;
            else if (mod > 0) i++;

            char spec = fmt[i];

            switch (spec) {
                case 'd': {
                    int32_t val;
                    switch (mod) {
                        case 1: val = (signed char)va_arg(args, int); break;
                        case 2: val = (short)va_arg(args, int); break;
                        case 3: /* long long non supportato su 32-bit */
                            val = (int32_t)va_arg(args, int32_t); break;
                        case 4: val = va_arg(args, long); break;
                        default: val = va_arg(args, int);
                    }
                    print_int32(val);
                    break;
                }
                case 'u':
                case 'x':
                case 'X': {
                    uint32_t val;
                    switch (mod) {
                        case 1: val = (unsigned char)va_arg(args, unsigned int); break;
                        case 2: val = (unsigned short)va_arg(args, unsigned int); break;
                        case 3: val = (uint32_t)va_arg(args, uint32_t); break;
                        case 4: val = va_arg(args, unsigned long); break;
                        default: val = va_arg(args, unsigned int);
                    }
                    int base = (spec == 'u') ? 10 : 16;
                    int uppercase = (spec == 'X') ? 1 : 0;
                    print_uint32(val, base, uppercase);
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char *);
                    print_string(s);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    print_char(c);
                    break;
                }
                case '%':
                    print_char('%');
                    break;
                default:
                    print_char('%');
                    print_char(spec);
                    break;
            }
        } else {
            print_char(fmt[i]);
        }
    }

    va_end(args);
}