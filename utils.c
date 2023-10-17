#include "main.h"

/**
 * is_printable - Check if a character is printable.
 * @c: Character to check.
 * Return: 1 if printable, 0 otherwise.
 */
int is_printable(char c)
{
	return ((c >= 32 && c < 127) ? 1 : 0);
}

/**
 * append_hexa_code - Append ASCII in hexadecimal code to buffer.
 * @buffer: Target buffer.
 * @i: Start position in buffer.
 * @ascii_code: ASCII value to convert.
 * Return: Always 3.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;
	buffer[i++] = '\\';
	buffer[i++] = 'x';
	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Check if a character is a digit.
 * @c: Character to check.
 * Return: 1 if digit, 0 otherwise.
 */
int is_digit(char c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

/**
 * convert_size_number - Convert number to specified size.
 * @num: Number to convert.
 * @size: Target size.
 * Return: Converted number.
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	if (size == S_SHORT)
		return ((short)num);
	return ((int)num);
}

/**
 * convert_size_unsgnd - Convert unsigned number to specified size.
 * @num: Number to convert.
 * @size: Target size.
 * Return: Converted number.
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	if (size == S_SHORT)
		return ((unsigned short)num);
	return ((unsigned int)num);
}
