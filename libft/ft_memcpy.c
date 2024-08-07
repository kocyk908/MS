/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:22:17 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/12 17:04:37 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	unsigned char		*dst;
	const unsigned char	*src;

	dst = destination;
	src = source;
	while (num > 0)
	{
		*dst = *src;
		dst++;
		src++;
		num--;
	}
	return (destination);
}

//int main() {
//	char dst[100];
//    char src[] = "This is Sparta!";
//    printf("Before: %s\n", dst);
//    ft_memcpy(dst, src, 5);
//    printf("After: %s\n", dst);

//    return 0;
//}
