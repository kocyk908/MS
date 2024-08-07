/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:00:15 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:26:42 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	char		*dst;
	const char	*src;

	dst = destination;
	src = source;
	if (src < dst)
	{
		while (num > 0)
		{
			dst[num - 1] = src[num - 1];
			num --;
		}
	}
	else
		ft_memcpy(destination, source, num);
	return (dst);
}

//#include "ft_memcpy.c"
//int main() {
//	char dst[100];
//    char src[] = "This is Sparta!";
//    printf("Before: %s\n", dst);
//    ft_memmove(dst, src, 5);
//    printf("After: %s\n", dst);

//    return 0;
//}

// LINE 27 is -1 becouse: Remember that array indexing in
// C is 0-based, so the valid indices are from 0 to num - 1, not from 1 to num.
