/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:05:05 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:29:19 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*temp;

	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			temp[j] = s[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

//int main()
//{
//	int *s;
//	printf("%s", ft_substr("This is Sparta!", 3, 4));
//}
