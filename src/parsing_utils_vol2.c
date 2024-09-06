/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/08/13 23:24:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strcspn(const char *str, const char *delim)
{
	const char	*s;
	const char	*d;

	s = str;
	while (*s)
	{
		d = delim;
		while (*d)
		{
			if (*s == *d)
				return (s - str);
			d++;
		}
		s++;
	}
	return (s - str);
}

size_t	ft_strspn(const char *str, const char *delim)
{
	const char	*s;
	const char	*d;

	s = str;
	while (*s)
	{
		d = delim;
		while (*d)
		{
			if (*s == *d)
				break ;
			d++;
		}
		if (*d == '\0')
			break ;
		s++;
	}
	return (s - str);
}

char	*add_space_at_start(char *input)
{
	char	*result;

	result = malloc(ft_strlen(input) + 2);
	if (!result)
		return (NULL);
	result[0] = ' ';
	ft_strcpy(result + 1, input);
	return (result);
}

int	size_checker(int exit_code)
{
	int	size;
	int	temp;

	temp = exit_code;
	size = 0;
	if (temp < 0)
	{
		size++;
		temp = -temp;
	}
	if (temp == 0)
		return (1);
	while (temp > 0)
	{
		temp /= 10;
		size++;
	}
	return (size);
}

char	*semi_itoa(int exit_code)
{
	static char	str[12];
	int			size;
	int			is_negative;

	is_negative = 0;
	size = size_checker(exit_code);
	str[size] = '\0';
	if (exit_code < 0)
	{
		is_negative = 1;
		exit_code = -exit_code;
	}
	while (size > 0)
	{
		str[--size] = (exit_code % 10) + '0';
		exit_code /= 10;
	}
	if (is_negative)
		str[0] = '-';
	return (str);
}
// Zakładamy maksymalnie 10 cyfr + 1 dla '-' + 1 dla '\0' temu str[12]