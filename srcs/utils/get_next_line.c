/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:09:35 by mberthou          #+#    #+#             */
/*   Updated: 2025/10/08 19:51:27 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_read_file(int fd, char **stash)
{
	char	*buffer;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_clear(stash), NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (ft_clear(&buffer), NULL);
	buffer[bytes_read] = '\0';
	return (buffer);
}

static char	*ft_fill_array(char *dest, char *src)
{
	char	*tmp;

	if (!src)
		return (NULL);
	if (!dest)
	{
		dest = ft_strdup(src);
		ft_clear(&src);
	}
	else
	{
		tmp = ft_strdup(dest);
		ft_clear(&dest);
		dest = ft_strjoin(tmp, src);
		ft_clear(&tmp);
		ft_clear(&src);
	}
	return (dest);
}

static char	*ft_extract_line(char **stash, char *end_of_line)
{
	char	*line;
	char	*tmp;
	int		len;

	if (end_of_line)
	{
		end_of_line++;
		len = end_of_line - *stash;
		line = ft_substr(*stash, 0, len);
		if (!line)
			return (ft_clear(stash), NULL);
		tmp = ft_strdup(end_of_line);
		if (!tmp)
			return (ft_clear(&line), ft_clear(stash), NULL);
	}
	else
	{
		line = ft_strdup(*stash);
		tmp = NULL;
	}
	ft_clear(stash);
	*stash = tmp;
	return (line);
}

__attribute__((destructor)) static void	_get_next_line_destroy(void)
{
	get_next_line(-1);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;
	char		*end_of_line;

	end_of_line = find_char(stash, '\n');
	while (!end_of_line)
	{
		buffer = ft_read_file(fd, &stash);
		if (!buffer)
		{
			if (stash && *stash)
			{
				line = ft_extract_line(&stash, NULL);
				return (line);
			}
			return (ft_clear(&stash), NULL);
		}
		stash = ft_fill_array(stash, buffer);
		if (!stash)
			return (NULL);
		end_of_line = find_char(stash, '\n');
	}
	line = ft_extract_line(&stash, end_of_line);
	return (line);
}
