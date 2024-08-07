/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:00:30 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:56:42 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < size -1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
	//printf("%s\n", dst);

//#include <stdio.h>
//int main()
//{
//size_t size = 3;
//char src[] = "coucou";
//char buffer[10];
//printf("lenght: %zu\n", ft_strlcpy(buffer, src, 0));
//printf("lenght: %zu\n", ft_strlcpy(buffer, src, 1));
//printf("lenght: %zu\n", ft_strlcpy(buffer, src, 2));
//printf("lenght: %zu\n", ft_strlcpy(buffer, src, 3));

//}
