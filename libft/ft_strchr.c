/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:01:08 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 13:44:51 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int z)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)z)
	{
		i++;
	}
	if (str[i] == (char)z)
	{
		return ((char *)&str[i]);
	}
	return ((char *) NULL);
}

//#include <stdio.h>
//int main()
//{
//	printf("%s", ft_strchr("This is a string or Sparta", 'a'));
//	printf("%s", ft_strchr("This is a string or Sparta", 0));

//	return (0);
//}
