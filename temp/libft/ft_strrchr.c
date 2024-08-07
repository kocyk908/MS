/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:36:25 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 13:08:20 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	counter;

	counter = 0;
	while (str[counter])
		counter++;
	while (counter >= 0)
	{
		if (str[counter] == (char)ch)
			return ((char *) str + counter);
		counter--;
	}
	return (NULL);
}

//#include <stdio.h>
//int main()
//{
//	printf("Place of last occurance: %s\n", ft_strrchr("shis is sparta!", 'p'));
//	printf("Place of last occurance: %s\n", ft_strrchr("shis is sparta!", 'z'));
//	printf("Place of last occurance: %s\n", ft_strrchr("", 't'));
//}
