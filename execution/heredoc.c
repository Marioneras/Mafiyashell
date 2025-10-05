/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:37:51 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/04 19:31:17 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

static char	*strip_quotes(char *limiter, bool *quoted)
{
	char	*tmp;

	if (nb_quote(limiter) == 1)
		(*quoted) = true;
	tmp = limiter;
	limiter = remove_quotes(tmp);
	return (limiter);
}

static void	process_input(char **line, bool quoted, char **envp, t_obj *obj)
{
	char	*tmp;
	(void)envp;
	if (quoted == false)
	{
		tmp = (*line);
		(*line) = expand_var(tmp, envp, obj);
		ft_clear(&tmp);
	}
	tmp = (*line);
	(*line) = ft_strjoin(tmp, "\n");
	ft_clear(&tmp);
}

int	handle_heredoc_error(char *limiter, int save_stdin, int save_stdout)
{
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	if (g_signal == SIGINT)
		return (130);
	if (g_signal == SIGQUIT)
		return (131);
	ft_putstr_fd("mafiyashell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	return (-2);
}

int	here_doc(char *limiter, char **envp, t_obj *obj)
{
	int		fd;
	int		save_stdin;
	int		save_stdout;
	char	*line;
	char	*tmp;
	bool	quoted;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	heredoc_signal();
	fd = open(".heredoc", O_RDWR | O_CREAT | O_EXCL, 0600);
	if (fd < 0)
		return (fd);
	quoted = false;
	tmp = limiter;
	limiter = strip_quotes(tmp, &quoted);
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\0')
			break ;
		process_input(&line, quoted, envp, obj);
		ft_putstr_fd(line, fd);
		line = readline("> ");
	}
	if (!line)
		return (handle_heredoc_error(limiter, save_stdin, save_stdout));
	else
		ft_clear(&line);
	child_signal();
	if (save_stdin >= 0)
		close(save_stdin);
	if (save_stdout >= 0)
		close(save_stdout);
	return (fd);
}
