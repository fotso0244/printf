#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
/**
 * print_format_c - prints a character
 * @c: a character
 * @nb: counter
 *
 * Return: a counter nb
 */
int print_format_c(char c, int nb)
{
	write(1, &c, 1);
	nb++;
	return (nb);
}
/**
 * printf_format_s - prints a string
 * @str: a string
 * @nb: counter
 *
 * Return: a counter nb
 */
int print_format_s(char *str, int nb)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			write(1, str, 1);
			str++;
			nb++;
		}
	}
	return (nb);
}
/**
 * _printf - prints all arguments
 * @format: pattern of arguments
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	int i = 0, nb = 0;
	va_list ap;
	char *p;

	va_start(ap, format);
	while (format[i] != '\0')
	{
		write(1, format + i, 1);
		i++;
		nb++;
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c')
			{
				nb = print_format_c(va_arg(ap, int), nb);
				i++;
			}
			if (format[i] == 's')
			{
				p = va_arg(ap, char *);
				nb = print_format_s(p, nb);
				i++;
			}
		}
	}
	return (nb);
}

