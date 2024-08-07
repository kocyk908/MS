/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:29:14 by pruszkie          #+#    #+#             */
/*   Updated: 2024/05/16 18:21:01 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}

// int main ()
//{
//    t_list *root, *el2, new_node;
//    root = malloc(sizeof(t_list));
//    root->content = "Head of the list";
//    el2 = malloc(sizeof(t_list));
//    root->next = el2;
//    el2->content = "Second element";
//    el2->next = NULL;

//    new_node.content = "New node";
//    new_node.next = NULL;

//    printf("%s\n", (char *)root->content);
//    printf("%s\n", (char *)el2->content);

//    ft_lstadd_back(&root, &new_node);

//    // printf("%s\n", (char *)new_node->content);
//    return (0);
//}
