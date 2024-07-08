/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:11:34 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/12 12:21:48 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && i < n - 1)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
//#include <stdio.h>
//int main()
//{
//	printf("str compare: %i\n", strncmp("Abcd", "abcd", 3));
//	printf("str compare: %i\n", strncmp("abed", "abcD", 3));
//	printf("str compare: %i\n", strncmp("abcd", "abCd", 3));
//	printf("str compare: %i\n", strncmp("2", "", 3));
//	printf("str compare: %i\n", strncmp("1234", "1235", 3));
//	printf("str compare: %i\n\n", strncmp("test\200", "test\0", 6));

//	printf("str compare: %i\n", ft_strncmp("Abcd", "abcd", 3));
//	printf("str compare: %i\n", ft_strncmp("abed", "abcD", 3));
//	printf("str compare: %i\n", ft_strncmp("abcd", "abCd", 3));
//	printf("str compare: %i\n", ft_strncmp("2", "", 3));
//	printf("str compare: %i\n", ft_strncmp("1234", "1235", 3));
//	printf("str compare: %i\n", ft_strncmp("test\200", "test\0", 6));
//	return (0);
//}
