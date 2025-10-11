/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:58:39 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 05:34:38 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error_message(int error_code, char *error_message)
{
	if (error_code == PIPE_ERROR)
		ft_putstr_fd("mafiyashell: syntax error near unexpected token `|'", 2);
	else if (error_code == MISSING_FILENAME)
		ft_putstr_fd
			("mafiyashell: syntax error near unexpected token `newline'", 2);
	else if (error_code == NO_COMMAND)
	{
		ft_putstr_fd("mafiyashell: ", 2);
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd(": command not found", 2);
	}
	else if (error_code == INVALID_OPERATOR)
	{
		ft_putstr_fd("mafiyashell: syntax error near unexpected token `", 2);
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd("'", 2);
	}
	else
	{
		ft_putstr_fd("mafiyashell: ", 2);
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(error_code), 2);
	}
	ft_putstr_fd("\n", 2);
}

int	redirection_error(char *str)
{
	ft_putstr_fd("mafiyashell: syntax error near unexpected token `", 2);
	if (ft_strlen(str) >= 4)
	{
		ft_putchar_fd(*str, 2);
		ft_putchar_fd(*str, 2);
	}
	else
		ft_putchar_fd(*str, 2);
	ft_putstr_fd("'\n", 2);
	return (INVALID_OPERATOR);
}

int	handle_heredoc_error(char *filename, char *limiter, t_fd save_fd, int fd)
{
	dup2(save_fd.save_stdin, STDIN_FILENO);
	dup2(save_fd.save_stdout, STDOUT_FILENO);
	if (g_signal == SIGINT)
		return (unlink(filename), close(fd), 130);
	if (g_signal == SIGQUIT)
		return (unlink(filename), close(fd), 131);
	ft_putstr_fd("mafiyashell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	return (fd);
}
