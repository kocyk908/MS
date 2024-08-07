/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:34:30 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:26:25 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char		ch;
	const unsigned char	*string;

	ch = c;
	string = str;
	while (n > 0)
	{
		if (*string == ch)
			return ((void *)string);
		string++;
		n--;
	}
	return (NULL);
}

//int main() {
//    char str[] = "This is Sparta!";
//    printf("Fount at: %s\n", ft_memchr(str, 'h', 5));
//    return 0;
//}
