/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:46:24 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:28:05 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}

//int main()
//{
//	printf("Total lenght of string: %zu\n", ft_strlen("This"));
//	printf("Total lenght of string: %zu\n", ft_strlen(""));
//	printf("Total lenght of string: %zu\n", ft_strlen(" "));
//}
