/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:58:31 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 12:55:29 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//#include <stdio.h>
//int main()
//{
//	printf("Is alnum: %d\n", ft_isalnum('d'));
//	printf("Is alnum: %d\n", ft_isalnum('3'));
//	printf("Is alnum: %d\n", ft_isalnum(-1));
//}
