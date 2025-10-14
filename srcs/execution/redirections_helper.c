/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:04:15 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/14 16:17:29 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_error(t_cmd *cmd, int input_fd, int output_fd)
{
	if (input_fd < 0)
	{
		if (cmd->outfile && output_fd > 0)
			close(output_fd);
		return (display_error_message(errno, cmd->infile), 1);
	}
	if (output_fd < 0)
	{
		if (cmd->infile && input_fd > 0)
			close(input_fd);
		return (display_error_message(errno, cmd->outfile), 1);
	}
	return (1);
}
