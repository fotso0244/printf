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
	char *s = "%cdebXfgiosux";

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
 * print_format_box - prints in format b, o, x and X
 * @i: an integer
 * @f: a format identifier
 * @nb: a counter
 *
 * Return: a counter
 */
int print_format_box(long int i, char f, int nb)
{
	char *s, *p;
	int size = -1, new_nb = nb, j;
	long int c, mod = 0, base, div = i;

	if (i < 0)
		div = UINT_MAX + 1 + i;
	if (i > UINT_MAX)
		div = i - UINT_MAX - 1;
	else
		div = i;
	c = div;
	if (f == 'b')
		base = 2;
	if (f == 'o')
		base = 8;
	if (f == 'x' || f == 'X')
		base = 16;
	if (i == 0)
	{
		write(1, "0", 1);
		return (nb + 1);
	}
	while (div != 0)
	{
		div /= base;
		size++;
	}
	size++;
	div = c;
	s = malloc(sizeof(*s) * size);
	if (s != NULL)
	{
		for (j = 0; j <= size - 2; j++)
		{
			mod = div % base;
			div /= base;
			if (mod < 10)
				s[j] = mod + 48;
			else
				if (f == 'x')
					s[j] = mod + 87;
				else
					if (f == 'X')
						s[j] = mod + 55;
		}
		if (div < 10)
			s[j] = div + 48;
		else
			if (f == 'x')
				s[j] = mod + 87;
			else
				if (f == 'X')
					s[j] = mod + 55;
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
 * print_format_diu - prints an integer
 * @i: an integer to print
 * @f: a format identifier
 * @nb: a counter
 *
 * Return: a counter
 */
int print_format_diu(long int i, char f, int nb)
{
	char *s, *p;
	int new_nb = nb, j, size = -1;
	long int mod = 0, c, div = i;

	if (i < 0 && f == 'u')
		div = UINT_MAX + 1 + i;
	
	if (i < 0 && (f == 'd' || f == 'i'))
	{
		div = i * (-1);
		size++;
	}
	else
		if (f == 'd' || f == 'i')
			div = i;
	c = div;
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
	div = c;
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
				if (format[i] == 'd' || format[i] == 'i' || format[i] == 'u')
					nb = print_format_diu(va_arg(ap, long int), format[i], nb), i++;
				if (format[i] == 'b' || format[i] == 'X' || format[i] == 'o' || format[i] == 'x')
					nb = print_format_box(va_arg(ap, long int), format[i], nb), i++;
			}
		}
	}
	else
		nb = -1;
	return (nb);
}
