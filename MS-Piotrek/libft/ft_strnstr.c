/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:07:59 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/12 13:31:37 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		while (little[j] == big[i + j] && little[j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
		j = 0;
	}
	return (NULL);
}

//#include <stdio.h>
//int main()
//{
//	printf("str compare: %s\n", ft_strnstr("look here nad here", "here", 4));
//	printf("str com: %s\n", ft_strnstr("look he her hera here", "here", -1));
//	printf("str compare: %s\n", ft_strnstr("look here", "hera", 4));
//	printf("str compare: %s\n", ft_strnstr("571684258", "68", 4));
//	printf("str compare: %s\n", ft_strnstr("abcd", " ", 4));
//	printf("str compare: %s\n", ft_strnstr("abcd", "", 4));
//	printf("str compare: %s\n", ft_strnstr("abcd", "", 4));
//	printf("str compare: %s\n", (ft_strnstr("aaabcabcd", "aabc", -1)));
//	return (0);
//}
