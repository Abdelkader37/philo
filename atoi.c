/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqrafi <aqrafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:12:30 by aqrafi            #+#    #+#             */
/*   Updated: 2025/08/01 16:41:46 by aqrafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_space(int c)
{
	return (((c >= 9 && c <= 13) || c == ' '));
}

int	is_digit(int c)
{
	return ((c >= '0' && c <= '9'));
}

long	ft_atoi(char *s)
{
	long	nmb;

	nmb = 0;
	while (*s && is_space(*s))
		s++;
	if (!*s)
		return (-1);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			return (-1);
		s++;
	}
	while (*s && is_digit(*s))
	{
		if (nmb * 10 + (*s - 48) < nmb)
			return (-1);
		nmb = nmb * 10 + (*s - 48);
		s++;
	}
	while (*s && is_space(*s))
		s++;
	if (*s && !is_digit(*s))
		return (-1);
	return (nmb);
}
