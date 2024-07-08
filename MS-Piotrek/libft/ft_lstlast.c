/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:29:37 by pruszkie          #+#    #+#             */
/*   Updated: 2024/05/16 18:22:00 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

// int main ()
// {
//     t_list root, node2, node3;
//     root.content = "head node";
//     root.next = &node2;
//     node2.content = "node2";
//     node2.next = &node3;
//     node3.content = "last node";
//     node3.next = NULL;

//     t_list *last_node = ft_lstlast(&root);
//     printf("Returned node: %s\n", (char *)last_node->content);
// }
