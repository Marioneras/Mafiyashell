/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:50:00 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/20 11:12:54 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*#include <stdio.h>

int	main(void)
{
  t_list *node;
  char *content ="Hello, world!";

  node = ft_lstnew(content);
  if (node == NULL)
  {
	printf("Memory allocation failed\n");
	return (1);
  }
  printf("Node content: %s\n", (char *)node->content);
  free(node);
  return (0);
}*/
