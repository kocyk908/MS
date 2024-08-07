/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:29:27 by pruszkie          #+#    #+#             */
/*   Updated: 2024/05/22 13:30:20 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head_new;
	t_list	*temp;

	if (f == NULL || del == NULL)
		return (NULL);
	head_new = NULL;
	new = NULL;
	while (lst != NULL)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			while (head_new)
			{
				temp = head_new->next;
				del(head_new->content);
				free(head_new);
				head_new = temp;
			}
		}
		ft_lstadd_back(&head_new, new);
		lst = lst->next;
	}
	return (head_new);
}

// int main()
// {
//     t_list root, node2, node3;
//     root.content = "head node";
//     root.next = &node2;
//     node2.content = "node2";
//     node2.next = &node3;
//     node3.content = "last node";
//     node3.next = NULL;
//     ft_lstmap(&root, &foo, &del_string);
// }
