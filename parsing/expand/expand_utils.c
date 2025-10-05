#include "minishell.h"

char	*process_segment(char *str, int *i, int start, char **envp, char *result, t_obj *obj)
{
	char	*prefsuf;
	char	*var;

	prefsuf = ft_substr(str, start, *i - start);
	if (prefsuf)
	{
		result = join_and_free(result, prefsuf);
		free(prefsuf);
	}
	var = after_dollar(str, i, envp, obj);
	if (var)
	{
		result = join_and_free(result, var);
		free(var);
	}
	return (result);
}

char	*append_remaining(char *str, int start, int i, char *result)
{
	char	*prefsuf;

	prefsuf = ft_substr(str, start, i - start);
	if (prefsuf)
	{
		result = join_and_free(result, prefsuf);
		free(prefsuf);
	}
	return (result);
}

char	*process_string(char *str, int *i, int *start, char **envp, char *result, t_obj *obj)
{
	while (str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] == '$')
		{
			char *prefsuf = ft_substr(str, *start, *i - *start);
			if (prefsuf)
			{
				char *tmp = join_and_free(result, prefsuf);
				if (tmp)
					result = tmp;
				free(prefsuf);
			}
			char *dollar = ft_strdup("$");
			if (dollar)
			{
				char *tmp = join_and_free(result, dollar);
				if (tmp)
					result = tmp;
				free(dollar);
			}
			*i += 2;
			*start = *i;
		}
		else if (str[*i] == '$')
		{
			result = process_segment(str, i, *start, envp, result, obj);
			*start = *i;
		}
		else
			(*i)++;
	}
	return (result);
}

char	*expand_var(char *str, char **envp, t_obj *obj)
{
	char	*result;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	result = process_string(str, &i, &start, envp, result, obj);
	if (start < i)
		result = append_remaining(str, start, i, result);
	return (result);
}