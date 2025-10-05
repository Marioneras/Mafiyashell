/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:42:47 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/21 17:05:59 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*new_list;
	void	*content;

	new_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		new_elem = ft_lstnew(content);
		if (!new_elem)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>

t_list	*ft_lstzero(void *lst)
{
  *(int *)content = 0;
  return (content);
}

void	del(void *content)
{
  free(content);
}

void	ft_printList(t_list *node)
{
  t_list *curr;

  curr = node;
  while (curr != NULL)
  {
    printf(" %d", *(int *)curr->content);
    curr = curr->next;
  }
  printf("\n");
}

int	main(void)
{
  t_list *new_list;
  t_list *temp;
	int	content[5];
  int i;

  void *(*f)(void *) = ft_lstzero;
  t_list list[5]
  content[5] = {1, 2, 3, 4, 5};
  i = 0;
  while (i < 5)
  {
    list[i] = ft_lstnew(&content[i]);
    if (!list[i])
    {
      printf("Memory allocation failed !");
      while (i-- > 0)
        free(list[i]);
      return (1);
    }
    i++;
  }
  i = 0;
  while (i < 4)
  {
    list[i].next = list[i + 1];
    i++;
  }
  list[4].next = NULL;
  printf("Linked list before modifications:");
  ft_printList(&list[0]);
  new_list = ft_lstmap(&list[0], f, del);
  printf("Linked list after modifications:");
  ft_printList(new_list);
    while (new_list)
    {
        temp = new_list->next;
        free(new_list);
        new_list = temp;
    }
  return (0);
}*/
