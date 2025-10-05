/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthou <mberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:19:42 by mberthou          #+#    #+#             */
/*   Updated: 2024/11/20 15:34:37 by mberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*#include <stdio.h>

void	printList(t_list *head)
{
	t_list	*curr;

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
  t_list *list[4];
  t_list *head;
  t_list *new_head;
  int content[] = {2, 3, 4, 5};
  int new_data = 1;
  int i;

  new_head = ft_lstnew(&new_data);
  i = 0;
  while (i < 4)
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
	while (i < 3)
	{
		list[i]->next = list[i + 1];
		i++;
	}
	list[3]->next = NULL;
	head = list[0];
  printf("Original Linked List:");
  printList(head);
  printf("After inserting Nodes at the front:");
  ft_lstadd_front(&head, new_head);
  printList(head);
  while (head != NULL)
    {
        t_list *temp = head;
        head = head->next;
        free(temp);
    }

    return (0);
}*/
