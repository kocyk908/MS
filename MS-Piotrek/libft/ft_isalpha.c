/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:10:38 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/06 16:41:22 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

/*#include <stdio.h>
int main()
{
	printf("Is alpha: %d\n", ft_isalpha('d'));
	printf("Is alpha: %d\n", ft_isalpha('1'));
	printf("Is alpha: %d\n", ft_isalpha(-1));
}*/
