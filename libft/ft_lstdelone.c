/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:30:23 by pruszkie          #+#    #+#             */
/*   Updated: 2024/05/16 18:21:43 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}
// void del_string(void *content)
//{
//	free(content);
//}

// int main()
//{
//	t_list *root;
//	root = malloc(sizeof(t_list));
//	root->content = (char *)malloc(sizeof(char) * strlen("To delete")+1);
//	strcpy(root->content, "To delete");
//	root->next = NULL;

//	printf("before deleting %s\n", (char *)root->content);

//	ft_lstdelone(root, &del_string);

//	printf("after deleting %s\n", (char *)root->content);
//}
