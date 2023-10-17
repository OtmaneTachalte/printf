#ifndef HEADER_MAIN_H
#define HEADER_MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_CAPACITY 1024
#define UNUSED_PARAM(x) (void)(x)

/* Format Flags */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* Sizing */
#define LONG_SIZE 2
#define SHORT_SIZE 1

/**
 * struct format_type - Struct mapping format to functions
 *
 * @format_char: The format character.
 * @f: Associated function.
 */
struct format_type
{
	char format_char;
	int (*f)(va_list, char[], int, int, int, int);
};

typedef struct format_type fmt_specifier;

int _printf(const char *format_string, ...);
int process_print(const char *fmt, int *index,
va_list args, char buffer[], int flags, int width, int precision, int specifier);

/******************* PRINTING HANDLERS *******************/

int print_char_function(va_list, char[], int, int, int, int);
int print_string_function(va_list, char[], int, int, int, int);
int print_percentage_function(va_list, char[], int, int, int, int);

int print_integer_function(va_list, char[], int, int, int, int);
int print_binary_function(va_list, char[], int, int, int, int);
int print_unsigned_function(va_list, char[], int, int, int, int);
int print_octal_function(va_list, char[], int, int, int, int);
int print_hex_function(va_list, char[], int, int, int, int);
int print_upper_hex_function(va_list, char[], int, int, int, int);

int print_non_visible_function(va_list, char[], int, int, int, int);
int print_memory_address_function(va_list, char[], int, int, int, int);

int fetch_flags(const char *format_string, int *index);
int fetch_width(const char *format_string, int *index, va_list args);
int fetch_precision(const char *format_string, int *index, va_list args);
int fetch_size(const char *format_string, int *index);

int print_reversed_string_function(va_list, char[], int, int, int, int);
int print_rot13_encoded_string_function(va_list, char[], int, int, int, int);

int handle_char_output(char character, char buffer[], int flags, int width, int precision, int size);
int output_integer(int is_positive, int buffer_index, char buffer[], int flags, int width, int precision, int size);
int output_number(int buffer_index, char buffer[], int flags, int width, int precision, int length, char padding, char additional_char);
int output_pointer_address(char buffer[], int buffer_index, int length, int width, int flags, char padding, char additional_char, int padding_start_index);
int output_unsigned_number(int is_negative, int buffer_index, char buffer[], int flags, int width, int precision, int size);

/********************** UTILITIES **********************/

int character_is_printable(char character);
int insert_hexadecimal_code(char character, char buffer[], int index);
int character_is_digit(char character);
long int adjust_numeric_size(long int number, int size);
long int adjust_unsigned_size(unsigned long int number, int size);

#endif /* HEADER_MAIN_H */
