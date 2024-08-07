/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:33:34 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:27:28 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char			*temp;
	unsigned int	counter;

	temp = (char *)malloc(ft_strlen(str) + 1);
	if (!temp)
		return (NULL);
	counter = 0;
	while (str[counter])
	{
		temp[counter] = str[counter];
		counter++;
	}
	temp[counter] = '\0';
	return (temp);
}

//#include "ft_strlen.c"
//int main()
//{
//	printf("%s", ft_strdup("This is Sparta!"));
//}

// LINE 22 it important to add +1 to value for NULL terminator
