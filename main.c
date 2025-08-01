/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqrafi <aqrafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:12:34 by aqrafi            #+#    #+#             */
/*   Updated: 2025/08/01 16:38:02 by aqrafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	t_arg	*arg;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error: Invalid argument\n", 25);
		return (1);
	}
	arg = init_arg(ac, av);
	if (!arg)
		return (1);
	init_fork(arg);
	create_threads(arg->nphilo, arg);
	destroy_fork(arg);
	free(arg);
}
