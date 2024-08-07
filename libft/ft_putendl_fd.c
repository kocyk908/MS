/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:55 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:37:55 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	counter;

	counter = 0;
	while (s[counter])
	{
		write(fd, &s[counter], 1);
		counter++;
	}
	write(fd, "\n", 1);
}
