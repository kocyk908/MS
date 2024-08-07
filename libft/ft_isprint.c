/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:41:14 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 13:05:36 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c >= 32 && c <= 126))
	{
		return (1);
	}
	return (0);
}

//#include <stdio.h>
//int main()
//{
//	printf("Is printable: %d\n", ft_isprint('d'));
//	printf("Is printable: %d\n", ft_isprint(' '));
//	printf("Is printable: %d\n", ft_isprint('~'));
//	printf("Is printable: %d\n", ft_isprint(177));
//	printf("Is printable: %d\n", ft_isprint(31));
//}
