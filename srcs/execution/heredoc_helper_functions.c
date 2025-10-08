/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:54:18 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 18:14:00 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_heredoc_file(void)
{
	static int	number = 0;
	char		*tmp_number;
	char		*file_name;

	tmp_number = ft_itoa(number++);
	if (!tmp_number)
		return (NULL);
	file_name = ft_strjoin(".heredoc", tmp_number);
	ft_clear(&tmp_number);
	if (!file_name)
		return (NULL);
	return (file_name);
}

void	process_input(char **line, bool quoted, t_obj *obj)
{
	char	*tmp;

	if (quoted == false)
	{
		tmp = (*line);
		(*line) = expand_var(tmp, obj->env, obj);
		ft_clear(&tmp);
	}
	tmp = (*line);
	(*line) = ft_strjoin(tmp, "\n");
	ft_clear(&tmp);
}

bool	is_end_of_input(const char *line, const char *limiter)
{
	return (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& line[ft_strlen(limiter)] == '\0');
}

int	open_heredoc_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (fd < 0)
		perror(filename);
	return (fd);
}

void	reset_fd(int save_stdin, int save_stdout)
{
	if (save_stdin >= 0)
		close(save_stdin);
	if (save_stdout >= 0)
		close(save_stdout);
}
