#include "main.h"

static void output_to_buffer(char buf[], int *buf_idx);

/**
 * _printf - Our printf implementation
 * @format: format string.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	int idx, char_count = 0, chars_printed = 0;
	int fmt_flags, fmt_width, fmt_precision, fmt_size, buf_idx = 0;
	va_list args;
	char buf[BUFF_SIZE];

	if (!format)
		return (-1);

	va_start(args, format);

	for (idx = 0; format && format[idx]; idx++)
	{
		if (format[idx] != '%')
		{
			buf[buf_idx++] = format[idx];
			if (buf_idx == BUFF_SIZE)
				output_to_buffer(buf, &buf_idx);
			char_count++;
		}
		else
		{
			output_to_buffer(buf, &buf_idx);
			fmt_flags = get_flags(format, &idx);
			fmt_width = get_width(format, &idx, args);
			fmt_precision = get_precision(format, &idx, args);
			fmt_size = get_size(format, &idx);
			++idx;
			chars_printed = handle_print(format, &idx, args, buf,
				fmt_flags, fmt_width, fmt_precision, fmt_size);
			if (chars_printed == -1)
				return (-1);
			char_count += chars_printed;
		}
	}

	output_to_buffer(buf, &buf_idx);

	va_end(args);

	return (char_count);
}

/**
 * output_to_buffer - Outputs the buffer contents
 * @buf: Character buffer
 * @buf_idx: Current buffer index, representing its size.
 */
static void output_to_buffer(char buf[], int *buf_idx)
{
	if (*buf_idx > 0)
		write(1, buf, *buf_idx);
	*buf_idx = 0;
}
