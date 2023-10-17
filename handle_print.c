#include "main.h"

/**
 * handle_print - Handles printing of formatted arguments.
 * @fmt: Format string with specifications for printing.
 * @list: List of arguments to be printed.
 * @ind: Current index in the format string.
 * @buffer: Buffer to hold the formatted output.
 * @flags: Flags for print formatting.
 * @width: Width specification for format.
 * @precision: Precision specification for format.
 * @size: Size specification for the argument.
 * Return: Number of characters printed or -1 for errors.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (i = 0; fmt_types[i].fmt; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (!fmt_types[i].fmt)
	{
		if (!fmt[*ind])
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
