/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:40:46 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/20 16:35:33 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/*#include <stdio.h>

int	main(void)
{
  int i;
  int content[] = {0, 1, 2, 3};
  t_list list[4];

  i = 0;
  while (i < 4)
  {
	list[i] = *ft_lstnew(&content[i]);
	i++;
  }
  i = 0;
  while (i < 3)
  {
	list[i].next = &list[i + 1];
		i++;
  }
  list[3].next = NULL;
  printf("la taille de la liste est de %d", ft_lstsize(list));
  return (0);
}*/
