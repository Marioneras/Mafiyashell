/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:46:54 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/20 17:51:24 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}

/*#include <stdio.h>

void	printList(t_list *node)
{
  t_list *curr;

  curr = head;
  while (curr != NULL)
  {
	printf(" %d", *(int *)curr->content);
	curr = curr->next;
  }
  printf("\n");
}

int	main(void)
{
  int i;
  int content[] = {0, 1, 2, 3, 4};
  t_list *list[5];

  i = 0;
  while (i < 5)
  {
	list[i] = ft_lstnew(&content[i]);
	if (!list[i])
	{
		printf("Memory allocation failed for node %d\n", i);
		while (i-- > 0)
		free(list[i]);
		return (1);
	}
	i++;
  }
  i = 0;
  while (i < 4)
  {
	list[i].next = &list[i + 1];
	i++;
  }
  list[4].next = NULL;
  printf("Orginal Linked List:");
  printList(list[0]);
  printf("After clearing the list from the middle:");
  ft_lstclear()
}*/
