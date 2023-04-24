#ifndef ACORAL_PRINT_H
#define ACORAL_PRINT_H
#include<type.h>
#include<print.h>
#include<string.h>
#include <stdio.h>
#include <stdarg.h>
acoral_32 acoral_print(const acoral_char *fmt, ...);
acoral_char acoral_putchar(acoral_char c);

void vprint(const char *fmt, va_list argp);
void my_printf(const char *fmt, ...); // custom printf() function


#endif
