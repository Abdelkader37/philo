#include "header.h"

int	main(int ac, char **av)
{
	t_arg *arg;
	if (ac != 5 && ac != 6)
	{
		write(2, "Error: Invalid argument\n", 25);
		return (1);
	}
	arg = init_arg(ac, av);
	init_fork(arg);
	create_threads(arg->nphilo, arg);
	destroy_fork(arg);
	free(arg);
}