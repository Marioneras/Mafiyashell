#include "minishell.h"

void    run_pwd(t_obj *obj)
{
    char *str;
    if (check_option(obj->cmd->argv) == 0)
    {
        ft_putstr_fd("pwd: No options\n", 2);
        return;
    }
    str = getcwd(NULL, 0);
    if (!str)
    {
        perror("");
        return;
    }
    else if (str)
        printf("%s\n", str);
    free(str);
    return;
}

int check_option(char **av)
{
    if (av[1] && av[1][0] == '-' && av[1][1] != '\0')
        return (0);
    return (1);
}
