
#include "minishell.h"

int run_env(t_obj *obj)
{
    int i;
    i = 0;
    if (check_option(obj->cmd->argv) == 0)
    {
        printf("env: No options\n");
        return (EXIT_FAILURE);
    }
    while (obj->env[i] != NULL)
    {
        ft_putstr_fd(obj->env[i], 2);
        write(1, "\n", 1);
        i++;
    }
	return (EXIT_SUCCESS);
}
