#include "header.h"

int	main(int ac, char **av)
{
	int nfilo;
	t_arg *arg;

	if (ac <= 4)
		return (1);
	arg = init_struct(ac, av);
	if (!arg)
		return (1);
	nfilo = ft_atoi(av[1]);
	creat_threads(nfilo, arg);
}