/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:22:22 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:26:20 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(int n)
{
	unsigned int	i;
	long			num;

	num = n;
	i = 1;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num >= 10)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	num;

	num = n;
	len = ft_len(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (num == 0)
	{
		str[0] = '0';
	}
	if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	str[len] = '\0';
	while (num > 0 && num != 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
//	int main()
//{
//	printf("%s\n", ft_itoa(-142));
//	//printf("%s\n", ft_itoa(6546));
//	//printf("%s\n", ft_itoa(8721469));
//	printf("%s", ft_itoa(0));
//}
