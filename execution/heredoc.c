/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:37:51 by mberthou          #+#    #+#             */
/*   Updated: 2025/09/04 19:31:17 by mberthnjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *limiter, char **envp)
{
	int		fd;
	char	*line;
	char	*tmp;
	bool	quoted;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_EXCL, 0600);
	if (fd < 0)
		return (fd);
	if (nb_quote(limiter) == 1)
		quoted = true;
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\0')
		{
			ft_clear(&line);
			break ;
		}
		if (quoted)
		{
			tmp = line;
			line = expand_var(tmp, envp);
			ft_clear(&tmp);
		}
		ft_putstr_fd(line, fd);
		line = readline("> ");
	}
	return (fd);
}
