/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:16:15 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:28:45 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		str = (char *)malloc(sizeof(char) * (j - i + 1));
		if (!str)
			return (NULL);
		if (str)
			ft_strlcpy(str, &s1[i], j - i + 1);
	}
	return (str);
}

//#include "ft_strchr.c"
//#include "ft_calloc.c"
//#include "ft_strlen.c"
//#include "ft_strdup.c"
//#include "ft_strlcpy.c"
//int main()
//{
//	printf("%s\n", ft_strtrim("ababaaaMy name is Simonbbaaabba", "ab"));
//	printf("%s\n", ft_strtrim("121212This 1212is12", "12"));
//	printf("%s\n", ft_strtrim("lilililiThis is", "1i"));
//}
