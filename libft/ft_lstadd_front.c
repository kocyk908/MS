/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:29:23 by pruszkie          #+#    #+#             */
/*   Updated: 2024/05/16 18:21:05 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main()
// {
//     t_list *lst = NULL; // Initialize lst to NULL
//     t_list *new = malloc(sizeof(t_list)); // Allocate memory for new node
//     if (new == NULL)
//     {
//         // Handle memory allocation error
//         return (1);
//     }
// }
//     // Assuming new node content needs to be initialized
//     // Example:
//     new->content = "New node content"; // Example content

//     // Set next pointer of new node to NULL since it will be the first node
//     new->next = NULL;

//     // Call ft_lstadd_front to add new node to the front of the list
//     ft_lstadd_front(&lst, new);

//     // Optional: You can print the content of the first node to verify
//     printf("Content of the first node: %s\n", (char *)lst->content);

//     // Remember to free allocated memory when done
//     free(new);

//     return (0);
// }
