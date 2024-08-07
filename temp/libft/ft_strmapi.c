/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:18:55 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:28:14 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned
int, char))
{
	unsigned int	index;
	unsigned int	len;
	char			*str;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	index = 0;
	while (index < len)
	{
		str[index] = f(index, s[index]);
		index++;
	}
	str[index] = '\0';
	return (str);
}

//char uppercase_char(unsigned int index, char c)
//{
//    if (c >= 'a' && c <= 'z')
//        return c - 32; // Convert lowercase to uppercase
//    return c;
//}

//int main()
//{
//    char *str = "hello world";
//    char *new_str = ft_strmapi(str, &uppercase_char);

//    if (new_str)
//    {
//        printf("%s\n", new_str);
//        free(new_str);
//    }
//    else
//    {
//        printf("Memory allocation failed.\n");
//    }

//    return 0;
//}
