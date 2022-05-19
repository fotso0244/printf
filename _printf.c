#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
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
 * print_format_s - prints a string
 * @str: a string
 * @nb: counter
 *
 * Return: a counter nb
 */
int print_format_s(char *str, int nb)
{
	if (str != 0x0)
	{
		while (*str != '\0')
		{
			write(1, str, 1);
			str++;
			nb++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		nb += 6;
	}
	return (nb);
}
/**
 * check - checks a character
 * @c: a character
 *
 * Return: 1 if true, otherwise 0
 */
int check(char c)
{
	char *s = "%cdefgiosux";

	while (*s != '\0')
	{
		if (*s != c)
			s++;
		else
			return (1);
	}
	return (0);
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

	va_start(ap, format);
	if (format != NULL)
	{
		if (format == NULL || strcmp(format, "%") == 0)
			return (-1);
		while (format[i] != '\0')
		{
			if (format[i] != '%' || (format[i] == '%' && check(format[i + 1]) == 0))
			{
				write(1, format + i, 1);
				i++, nb++;
			}
			if (format[i] == '%')
			{
				i++;
				if (format[i] == '%')
				{
					write(1, "%", 1);
					nb++, i++;
				}
				if (format[i] == 'c')
					nb = print_format_c(va_arg(ap, int), nb), i++;
				if (format[i] == 's')
					nb = print_format_s(va_arg(ap, char *), nb), i++;
			}
		}
	}
	else
		nb = -1;
	return (nb);
}
