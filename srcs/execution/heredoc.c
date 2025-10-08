/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:37:51 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 18:13:57 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_quotes(char *limiter, bool *quoted)
{
	char	*tmp;

	if (nb_quote(limiter) == 1)
		(*quoted) = true;
	tmp = limiter;
	if (quoted)
		limiter = remove_quotes(tmp);
	return (limiter);
}

static int	handle_ctrl_c(char *filename, char *limiter, int save_stdin,
	int save_stdout)
{
	int	fd;

	fd = handle_heredoc_error(filename, limiter, save_stdin, save_stdout);
	reset_fd(save_stdin, save_stdout);
	return (fd);
}

static void	write_heredoc_line(int fd, char **line, bool quoted, t_obj *obj)
{
	process_input(line, quoted, obj);
	ft_putstr_fd(*line, fd);
	ft_clear(line);
}

int	here_doc(t_obj *obj, char *file, char *limit)
{
	int		fd;
	t_fd	s_fd;
	char	*line;
	char	*tmp;
	bool	quoted;

	s_fd.save_stdin = dup(STDIN_FILENO);
	s_fd.save_stdout = dup(STDOUT_FILENO);
	heredoc_signal();
	fd = open_heredoc_file(file);
	if (fd < 0)
		return (fd);
	tmp = limit;
	limit = strip_quotes(tmp, &quoted);
	line = readline("> ");
	while (line && is_end_of_input(line, limit))
	{
		write_heredoc_line(fd, &line, quoted, obj);
		line = readline("> ");
	}
	if (!line)
		return (handle_ctrl_c(file, limit, s_fd.save_stdin, s_fd.save_stdout));
	ft_clear(&line);
	child_signal();
	return (reset_fd(s_fd.save_stdin, s_fd.save_stdout), ft_clear(&limit), fd);
}
