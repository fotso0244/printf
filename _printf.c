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
int print_format_boxp(long int i, char f, int nb);
/**
 * print_format_sS - prints a string
 * @str: a string
 * @f: a format identifier
 * @nb: counter
 *
 * Return: a counter nb
 */
int print_format_sS(char *str, char f, int nb)
{
	int new_nb = nb;
	if (str != 0x0)
	{
		while (*str != '\0')
		{
			if (((*str > 0 && *str < 32) || (*str >= 127)) && (f == 'S'))
			{
				if (*str <= 15)
				{
					write(1, "\\x0",3);
					new_nb += 3;
				}
				else
				{
					write(1, "\\x",2);
					new_nb += 2;
				}
				new_nb = print_format_boxp(*str, 'X', new_nb);
				str++;
			}
			if (*str != '\0' && *str >= 32 && *str < 127)
			{
				write(1, str, 1);
				str++;
				new_nb++;
			}
		}
	}
	else
	{
		write(1, "(null)", 6);
		new_nb += 6;
	}
	return (new_nb);
}
/**
 * check - checks a character
 * @c: a character
 *
 * Return: 1 if true, otherwise 0
 */
int check(char c, char *s)
{
	/*char *s = "% +cdpebXfgiosuxS#";*/

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
 * print_format_lbox - prints in format b, o, x and X
 * @i: an integer
 * @f: a format identifier
 * @nb: a counter
 *
 * Return: a counter
 */
int print_format_lbox(unsigned long int i, char f, int nb)
{
	char *s, *p;
	int size = -1, new_nb = nb, j;
	unsigned long int c, mod = 0, base, div = i;

	if (i > ULONG_MAX && (f == 'b' || f == 'X' || f == 'o' || f == 'x'))
		div = i - ULONG_MAX - 1;
	c = div;
	if (f == 'b')
		base = 2;
	if (f == 'o')
		base = 8;
	if (f == 'x' || f == 'X')
		base = 16;
	if (i == 0 && (f == 'o' || f == 'b' || f == 'x' || f == 'X'))
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
	mod = div % base;
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
				s[j] = div + 87;
			else
				if (f == 'X')
					s[j] = div + 55;
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
	free(s);
	return (new_nb);
}
/**
 * print_format_boxp - prints in format b, o, x and X
 * @i: an integer
 * @f: a format identifier
 * @nb: a counter
 *
 * Return: a counter
 */
int print_format_boxp(long int i, char f, int nb)
{
	char *s, *p;
	int size = -1, new_nb = nb, j;
	long int c, mod = 0, base, div = i;

	if (i < 0 && (f == 'b' || f == 'o' || f == 'x' || f == 'X'))
		div = UINT_MAX + 1 + i;
	if (i < 0 && f == 'p')
		div = LONG_MAX + i + 1;
	if (i > UINT_MAX && (f == 'b' || f == 'X' || f == 'o' || f == 'x'))
		div = i - UINT_MAX - 1;
	c = div;
	if (f == 'b')
		base = 2;
	if (f == 'o')
		base = 8;
	if (f == 'x' || f == 'p' || f == 'X')
		base = 16;
	if (i == 0 && (f == 'o' || f == 'b' || f == 'x' || f == 'X'))
	{
		write(1, "0", 1);
		return (nb + 1);
	}
	if (i == 0 && f == 'p')
	{
		write(1, "(nil)", 5);
		return (nb + 5);
	}
	while (div != 0)
	{
		div /= base;
		size++;
	}
	size++;
	div = c;
	if (f == 'p')
		write(1, "0x", 2), new_nb += 2;
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
				if (f == 'x' || f == 'p')
					s[j] = mod + 87;
				else
					if (f == 'X')
						s[j] = mod + 55;
		}
		if (div < 10)
			s[j] = div + 48;
		else
			if (f == 'x')
				s[j] = div + 87;
			else
				if (f == 'X')
					s[j] = div + 55;
		if (div < 10 && i < 0 && f == 'p')
			s[j] = 'f';
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
	free(s);
	return (new_nb);
}

/**
 * print_format_lu - prints an integer
 * @i: an integer to print
 * @f: a format identifier
 * @nb: a counter
 *
 * Return: a counter
 */
int print_format_lu(unsigned long int i, char f, int nb)
{
	char *s, *p;
	int new_nb = nb, j, size = -1;
	unsigned long int mod = 0, c, div;

	/*if (i < 0 && f == 'u')
		div = ULONG_MAX + 1 + i;*/
	if (i > ULONG_MAX && f == 'u')
		div = i - ULONG_MAX - 1;
	/*if (i == LONG_MIN)
		div = LONG_MAX;
	if (i < 0 && (f == 'd' || f == 'i'))
	{
		if (i != LONG_MIN)
			div = i * (-1);
		size++;
	}
	else
		if ((f == 'd' || f == 'i') && i != LONG_MIN)
			div = i;*/
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
			/*if (i == LONG_MIN && j == 0)
				s[j] = '8';*/
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
	free(s);
	return (new_nb);
}
/**
 * print_format_ldi - prints an integer
 * @i: an integer to print
 * @f: a format identifier
 * @nb: a counter
 *
 * Return: a counter
 */
int print_format_ldi(long int i, char f, int nb)
{
	char *s, *p;
	int new_nb = nb, j, size = -1;
	long int mod = 0, c, div;

	/*if (i < 0 && f == 'u')
		div = ULONG_MAX + 1 + i;
	if ((unsigned long)i > ULONG_MAX && f == 'u')
		div = i - ULONG_MAX - 1;*/
	if (i == LONG_MIN)
		div = LONG_MAX;
	if (i < 0 && (f == 'd' || f == 'i'))
	{
		if (i != LONG_MIN)
			div = i * (-1);
		size++;
	}
	else
		if ((f == 'd' || f == 'i') && i != LONG_MIN)
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
			if (i == LONG_MIN && j == 0)
				s[j] = '8';
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
	free(s);
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
int print_format_diu(int i, char f, int nb)
{
	char *s, *p;
	int new_nb = nb, j, size = -1;
	long int mod = 0, c, div = (long int)i;

	if (i < 0 && f == 'u')
		div = UINT_MAX + 1 + i;
	if ((unsigned int)i > UINT_MAX && f == 'u')
		div = i - UINT_MAX - 1;
	
	if (i < 0 && (f == 'd' || f == 'i'))
	{
		div = (long int)i * (-1);
		size++;
	}
	else
		if (f == 'd' || f == 'i')
			div = (long int)i;
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
	free(s);
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
	int i = 0, nb = 0, mark = 0;
	char *s2 = "oxXpcsSu", *s1 = "l% +cdpebXfgiosuxS#h";
	long int l;
	va_list ap;

	va_start(ap, format);
	if (format == NULL || strcmp(format, "%") == 0 || strcmp(format, "% ") == 0)
		return (-1);
	if (format != NULL)
	{i = 0;
		while (format[i] != '\0')
		{
			if (format[i] != '%' || (format[i] == '%' && check(format[i + 1], s1) == 0))
			{
				write(1, format + i, 1);
				i++;
				nb++;
			}
			if (format[i] == '%' && check(format[i + 2], s1) == 0 &&(format[i + 1] == 'h' || format[i + 1] == 'l'))
			{
				write(1, "%", 1);
				i += 2;
				nb++;
			}
			if (format[i] == '%')
			{
				i++;
				if (format[i] == ' ' && format[i + 1] == '%')
					i++;
				if ((format[i] == 'h' || format[i] == 'l') && check(format[i + 1], s2) == 0)
				{
					if (format[i] == 'h')
						l = va_arg(ap, int);
					else
						l = va_arg(ap, long int);
					mark = 1;
					i++;
				}

				if ((format[i] == 'h' || format[i] == 'l') && (format[i + 1] == 'u' || format[i + 1] == 'o' || format[i + 1] == 'x' || format[i + 1] == 'X'))
				{
					l = va_arg(ap, unsigned long int);
					mark = 1;
					i++;
				}
				if (format[i] == '+' || format[i] == ' ' || format[i] == '%' || format[i] == '#')
				{
					i++;
					if (format[i] == 'd' || format[i] == 'i' || format[i] == 'u' || check(format[i + 1], s2) == 0)
					{
						l = va_arg(ap, int);
						mark = 1;
					}
					if (format[i] == '#')
					{
						l = va_arg(ap, long int);
						if (format[i + 1] == 'o' && l != 0)
							write(1, "0", 1), nb++;
						if (format[i + 1] == 'x' && l != 0)
						{
							write(1, "0x", 2);
							nb += 2;
						}
						if (format[i + 1] == 'X' && l != 0)
						{
							write(1, "0X", 2);
							nb += 2;
						}
					}
					if (format[i] == '%')
					{
						write(1, "%", 1);
						nb++;
					}
					if (format[i] == '+' && l >= 0 && (format[i + 1] == 'd' || format[i + 1] == 'i'))
						write(1, "+", 1), nb++;
					if (format[i] == '+' && l >= 0 && format[i + 1] == ' ')
					{
						write(1, "+", 1);
						nb += 1, i++;
					}
					if (format[i] == ' ' && format[i - 1] != '+' && l >= 0 && (format[i + 1] == 'd' || format[i + 1] == 'i'))
						write(1, " ", 1), nb++;
					i++;
					if (format[i] == '+' && l < 0)
						i++;
				}
				if (format[i] == 'c')
					nb = print_format_c(va_arg(ap, int), nb), i++;
				if (format[i] == 's' || format[i] == 'S')
				{
					nb = print_format_sS(va_arg(ap, char *), format[i], nb);
					i++;
				}
				if (format[i] == 'd' || format[i] == 'i' || format[i] == 'u')
				{
					if (!mark)
						l = va_arg(ap, int);
					if (format[i - 1] == '%')
						nb = print_format_diu(l, format[i], nb);
					if ((format[i - 1] == 'l' || format[i - 1] == 'h') && format[i] != 'u')
						nb = print_format_ldi(l, format[i], nb);
					if ((format[i - 1] == 'l' || format[i - 1] == 'h') && format[i] == 'u')
						nb = print_format_lu(l, format[i], nb);
					i++;
				}
				if (format[i] == 'p')
					nb = print_format_boxp((long int)va_arg(ap, void *), format[i], nb), i++;
				if (format[i] == 'b' || format[i] == 'X' || format[i] == 'o' || format[i] == 'x')
				{
					if (format[i - 1] == '%')
						nb = print_format_boxp(va_arg(ap, long int), format[i], nb);
					if (format[i - 1] == 'l' || format[i - 1] == 'h')
						nb = print_format_lbox(l, format[i], nb);
					i++;
				}
			}
		}
	}
	else
		nb = -1;
	return (nb);
}
