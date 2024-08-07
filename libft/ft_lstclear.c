/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:30:39 by pruszkie          #+#    #+#             */
/*   Updated: 2024/05/16 18:21:17 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		prev = (*lst);
		del((*lst)->content);
		(*lst) = (*lst)->next;
		free(prev);
	}
}

// int main()
//{
//	t_list *root, *node2, *node3;
//	root = malloc(sizeof(t_list));
//	node2 = malloc(sizeof(t_list));
//	node3 = malloc(sizeof(t_list));
//	root->content = (char *)malloc(sizeof(char) * strlen("First node")+1);
//	strcpy(root->content, "First node");
//	root->next = node2;
//	node2->content = (char *)malloc(sizeof(char) * strlen("Second node")+1);
//	strcpy(root->content, "Second node");
//	node2->next = node3;
//	node3->content = (char *)malloc(sizeof(char) * strlen("Last node")+1);
//	strcpy(root->content, "Last node");
//	node3->next = NULL;

//	printf("Content of root: %s\n", (char *)root->content);
//	printf("Content of node2: %s\n", (char *)root->content);
//	printf("Content of node3: %s\n", (char *)root->content);

//	ft_lstclear(&root, &del);

//	printf("Content of root: %s\n", (char *)root->content);
//	printf("Content of node2: %s\n", (char *)root->content);
//	printf("Content of node3: %s\n", (char *)root->content);
//}
