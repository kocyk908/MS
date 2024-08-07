/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:55:25 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/06 16:42:26 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

/*#include <stdio.h>
int main()
{
	printf("Is digit: %d\n", ft_isdigit('d'));
	printf("Is digit: %d\n", ft_isdigit('1'));
	printf("Is digit: %d\n", ft_isdigit(-1));
}*/
