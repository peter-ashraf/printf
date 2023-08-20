#include "main.h"

void print_buffer(char buffer[], int *buff_ind);


/**
 * _printf - function that prints anything
 * @format: the string to print
 *
 * Return: number of chars printed
 */

int _printf(const char *format, ...)
{
	int i, count = 0, total = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list args;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];
			if (buffer_index == BUFFER_SIZE)
				print_buffer(buffer, &buffer_index);
			total++;
		}
		else
		{
			print_buffer(buffer, &buffer_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			count = handle_print(format, &i, args, buffer, flags, width, precision, size);
			if (count == -1)
				return (-1);
			total += count;
		}
	}

	print_buffer(buffer, &buffer_index);

	va_end(args);

	return (total);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffer_index: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}
