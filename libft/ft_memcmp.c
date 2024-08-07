/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:56:51 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:49:19 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((int)s1[i] - (int)s2[i]);
		i++;
	}
	return (0);
}

//int main()
//{
//	int arr[1] = {1,2};
//	int arr2[5] = {1,4,3,4,5};
//	arr[0];
//	arr[1];
//	char *str = "abCd";
//	char *str2 = "abcd";
//	printf("%d\n", ft_memcmp(arr, arr2, 6));
//	printf("%d", ft_memcmp(str, arr2, 6));

//}
