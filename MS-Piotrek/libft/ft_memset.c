/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:15:01 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/12 17:19:20 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*p;

	p = ptr;
	while (num > 0)
	{
		p[num - 1] = value;
		num--;
	}
	return (ptr);
}

//int main() {
//    char str[] = "ThisisSparta!";
//    printf("Before: %s\num", str);
//    ft_memset(str, 'x', 3);
//    printf("After: %s\n", str);

//    return 0;
//}

// line 25 return function in this case is corract
