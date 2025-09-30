#include "minishell.h"

int new_tab(t_obj *obj, int a)
{
    char **new;
    int len;

    len = ft_tabcount(obj->env) + 2;
    new = malloc(sizeof(char *) * len);
    if (!new)
        return 0;

    if (!clone(obj, new, a))
    {
        free(new);
        return 0;
    }
    char **old_env = obj->env;
    obj->env = new;
    ft_freetab(old_env);
    return 1;
}


int run_export(t_obj *obj)
{
    int		i;
    char	**clone_av;

    if (check_option(obj->cmd->argv) == 0)
    {
        ft_putstr_fd("export: No options\n", 2);
        return (EXIT_FAILURE);
    }
    i = 1;
    clone_av = clone_env(obj->cmd->argv);
    while (clone_av[i] != NULL)
    {
        if (!new_tab(obj, i))
        {
            ft_freetab(clone_av);
			return (EXIT_FAILURE);
        }
        i++;
    }
    ft_freetab(clone_av);
	return (EXIT_SUCCESS);
}

int clone(t_obj *obj, char **clone, int a)
{
    int i;

    i = 0;
    while (obj->env[i] != NULL)
    {
        clone[i] = ft_strdup(obj->env[i]);
        if (!clone[i])
        {
            ft_freetab(clone);
            return 0;
        }
        i++;
    }

    clone[i] = ft_strdup(obj->cmd->argv[a]);
    if (!clone[i])
    {
        ft_freetab(clone);
        return 0;
    }

    clone[i + 1] = NULL;
    return 1;
}

void ft_freetab(char **tab)
{
    int i;

    i = 0;
    while (tab[i] != NULL)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
