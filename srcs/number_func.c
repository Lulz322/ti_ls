#include "../includes/ft_ls.h"

void funcing_itoa(off_t number, char size[4]) {
	int len;
	off_t d;

	d = number;
	len = 0;
	while (d >= 1)
	{
		d /= 10;
		len++;
	}
	while (--len > -1)
	{
		size[len] = number % 10 + 48;
		number /= 10;
	}
	size[4] = '\0';
}

void primetive(off_t number, char size[4], char c)
{
	off_t ostacha;
	while (number > 1024)
	{
		ostacha = number % 1024;
		number /= 1024;
	}
	if (ostacha > 0)
		number++;
	funcing_itoa(number, size);
	ft_strcat(size, &c);
	size[4] = '\0';
}

long double roundNo(long double num)
{
    return num < 0 ? num - 0.05 : num + 0.05;
}

void kb(off_t number, char size[4], char c)
{
	long double a;
	a = (long double)number;
	char *str;

	str = myfloat(a);
	a = roundNo(a);
	size[0] = str[0];
	size[1] = '.';
	size[2] = str[1];
	size[3] = c;
	size[4] = '\0';
	free(str);
}

void bytes(off_t number, char size[4])
{
	if (number < 1024)
		funcing_itoa(number, size);
	else if (number < 10240)
		kb(number, size, 'K');
	else if (number < 1024000)
		primetive(number, size, 'K');
	else if (number < 10240000)
		kb(number, size, 'M');
	else if (number < 10240000000)
		primetive(number, size, 'M');
	else if (number < 102400000000)
		kb(number, size, 'G');
	else if (number < 10240000000000)
		primetive(number, size, 'G');
}
