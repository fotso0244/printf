#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
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
	char *s = "%cdebfgiosux";

	while (*s != '\0')
	{
		if (*s != c)
			s++;
		else
			return (1);
	}
	return (0);
}
int print_format_b(long int i, int nb)
{
	char *s, *p;
	int size = -1, new_nb = nb, j;
	long int mod = 0, div = i;

	if (i == 0)
	{
		write(1, "0", 1);
		return (nb + 1);
	}
	while (div != 0)
	{
		div /= 2;
		size++;
	}
	size++;
	if (i < 0)
	{
		div = UINT_MAX + 1 + i;
		/*size++;*/
	}
	else
		div = i;
	s = malloc(sizeof(*s) * size);
	if (s != NULL)
	{
		for (j = 0; j <= size - 2; j++)
		{
			mod = div % 2;
			div /= 2;
			s[j] = mod + 48;
		}
		s[j] = div + 48;
		/*if (i < 0)
			s[size - 1] = '-';*/
		s[size] = '\0';
		j = 0;
		p = s + size - 1;
		while (j != size - 1)
		{
			write(1, p, 1);
			p--;
			j++;
			new_nb++;
		}
		write(1, p, 1);
		new_nb++;
	}
	return (new_nb);
}
/**
 * print_format_di - prints an integer
 * @i: an integer to print
 * @nb: a counter
 *
 * Return: a counter
 */
int print_format_di(int i, int nb)
{
	char *s, *p;
	int new_nb = nb, j, size = -1;
	long int mod = 0, div = (long int)i;

	if (i == 0)
	{
		write(1, "0", 1);
		return (nb + 1);
	}
	while (div != 0)
	{
		div /= 10;
		size++;
	}
	size++;
	if (i < 0)
	{
		div = (long int)i * (-1);
		size++;
	}
	else
		div = (long int)i;
	s = malloc(sizeof(*s) * (size + 1));
	if (s != NULL)
	{
		for (j = 0; j <= size - 2; j++)
		{
			mod = div % 10;
			div /= 10;
			s[j] = mod + 48;
		}
		s[j] = div + 48;
		if (i < 0)
			s[size - 1] = '-';
		s[size] = '\0';
		j = 0;
		p = s + size - 1;
		while (j != size - 1)
		{
			write(1, p, 1);
			p--;
			j++;
			new_nb++;
		}
		write(1, p, 1);
		new_nb++;
	}
	return (new_nb);
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
				if (format[i] == 'd' || format[i] == 'i')
					nb = print_format_di(va_arg(ap, int), nb), i++;
				if (format[i] == 'b')
					nb = print_format_b(va_arg(ap, long int), nb), i++;
			}
		}
	}
	else
		nb = -1;
	return (nb);
}
