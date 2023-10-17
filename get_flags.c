#include "main.h"

/**
 * get_flags - Determines active flags from format string.
 * @format: Formatted string containing the flags.
 * @i: Current position in format string.
 * Return: Computed flags.
 */
int get_flags(const char *format, int *i)
{
	int index, current_position;
	int computed_flags = 0;
	const char FLAGS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_position = *i + 1; format[current_position]; current_position++)
	{
		for (index = 0; FLAGS[index]; index++)
			if (format[current_position] == FLAGS[index])
			{
				computed_flags |= FLAGS_VALUES[index];
				break;
			}

		if (!FLAGS[index])
			break;
	}

	*i = current_position - 1;
	return (computed_flags);
}
