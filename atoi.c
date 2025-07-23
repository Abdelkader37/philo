#include "header.h"

int	is_space(char c)
{
	return (((c >= 9 && c <= 13) || c == 32));
}

int	is_num(int c)
{
	return ((c >= '0' && c <= '9'));
}

unsigned long	ft_atoi(char *str)
{
	unsigned long	num;

	num = 0;
	while (*str && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (0);
		str++;
	}
	while (*str && is_num(*str))
	{
		num = num * 10 + (*str - 48);
		str++;
	}
	if (*str && !is_num(*str))
		return (0);
	return (num);
}
