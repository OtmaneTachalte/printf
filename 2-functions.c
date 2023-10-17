#include "main.h"

/**
 * display_pointer - Outputs the value of a pointer variable
 * @args: Variable arguments list
 * Return: Count of characters printed
 */
int display_pointer(va_list args)
{
	unsigned long addr_val;
	char *hexa_map = "0123456789abcdef";
	char output_buffer[20];
	int idx = 0;

	addr_val = (unsigned long)va_arg(args, void *);
	if (!addr_val)
		return (write(1, "(nil)", 5));

	output_buffer[idx++] = '0';
	output_buffer[idx++] = 'x';
	while (addr_val)
	{
		output_buffer[idx++] = hexa_map[addr_val % 16];
		addr_val /= 16;
	}
	output_buffer[idx] = '\0';

	return (write(1, output_buffer, idx));
}

/**
 * output_non_print_chars - Outputs non-printable characters in hex format
 * @args: Variable arguments list
 *
 * Return: Count of characters printed
 */
int output_non_print_chars(va_list args)
{
	char *input_str = va_arg(args, char *);
	char output_buffer[500];
	int idx = 0, buf_idx = 0;

	while (input_str[idx])
	{
		char current_char = input_str[idx++];

		if (current_char >= 32 && current_char < 127)
			output_buffer[buf_idx++] = current_char;
		else
		{
			output_buffer[buf_idx++] = '\\';
			output_buffer[buf_idx++] = 'x';
			output_buffer[buf_idx++] =
				"0123456789ABCDEF"[(current_char / 16) % 16];
			output_buffer[buf_idx++] =
				"0123456789ABCDEF"[current_char % 16];
		}
	}
	output_buffer[buf_idx] = '\0';

	return (write(1, output_buffer, buf_idx));
}

/**
 * display_reversed - Outputs a reversed string
 * @args: Variable arguments list
 *
 * Return: Count of characters printed
 */
int display_reversed(va_list args)
{
	char *input_str = va_arg(args, char *);
	int str_len = 0;

	if (!input_str)
		input_str = "(null)";

	while (input_str[str_len])
		str_len++;

	for (int i = str_len - 1; i >= 0; i--)
		write(1, &input_str[i], 1);

	return (str_len);
}

/**
 * display_rot13 - Outputs a string transformed to ROT13
 * @args: Variable arguments list
 *
 * Return: Count of characters printed
 */
int display_rot13(va_list args)
{
	char *original_str = va_arg(args, char *);
	char regular_alphabet[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char rot13_alphabet[] =
		"NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	int count = 0;

	for (int i = 0; original_str[i]; i++)
	{
		char ch = original_str[i];
		int matched = 0;

		for (int j = 0; j < 52; j++)
		{
			if (ch == regular_alphabet[j])
			{
				write(1, &rot13_alphabet[j], 1);
				matched = 1;
				count++;
				break;
			}
		}
		if (!matched)
		{
			write(1, &ch, 1);
			count++;
		}
	}
	return (count);
}
