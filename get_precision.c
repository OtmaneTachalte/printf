#include "main.h"

/**
 * get_precision - Extracts precision from format string.
 * @format: The format string.
 * @i: Current position in the format string.
 * @list: List of arguments.
 * Return: The determined precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int current_position = *i + 1;
	int precision = -1;

	/* Check if next character is a period, indicating precision specification */
	if (format[current_position] != '.')
		return (precision);

	precision = 0;
	current_position++;

	/* Parse the precision value */
	while (format[current_position])
	{
		if (is_digit(format[current_position]))
		{
			precision = (precision * 10) + (format[current_position] - '0');
			current_position++;
		}
		else if (format[current_position] == '*')
		{
			precision = va_arg(list, int);
			current_position++;
			break;
		}
		else
			break;
	}

	*i = current_position - 1;
	return (precision);
}
