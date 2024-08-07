/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:30 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/06 16:41:56 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
	{
		return (1);
	}
	return (0);
}

/*#include <stdio.h>
int main()
{
	printf("Is ascii: %d\n", ft_isascii('d'));
	printf("Is ascii: %d\n", ft_isascii('1'));
	printf("Is ascii: %d\n", ft_isascii(-1));
	printf("Is ascii: %d\n", ft_isascii(128));
}*/
