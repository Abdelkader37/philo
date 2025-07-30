#include "header.h"

int	is_space(int c)
{
	return (((c >= 9 && c <= 13) || c == ' '));
}

int	is_digit(int c)
{
	return ((c >= '0' && c <= '9'));
}

unsigned long	ft_atoi(char *s)
{
	int	nmb;

	nmb = 0;
	while (*s && is_space(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			return (0);
		s++;
	}
	while (*s && is_digit(*s))
	{
		nmb = nmb * 10 + (*s - 48);
		s++;
	}
	while (*s && is_space(*s))
		s++;
	if (*s && !is_digit(*s))
		return (0);
	return (nmb);
}
