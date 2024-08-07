/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:07:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:23:47 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temp;
	size_t			counter;

	if (size == 0 || nmemb == 0)
	{
		size = 1;
		nmemb = 1;
	}
	if (size > 2147483647 / nmemb)
	{
		return (NULL);
	}
	temp = (void *)malloc(nmemb * size);
	if (!temp)
		return (NULL);
	counter = 0;
	while ((nmemb * size) > counter)
	{
		temp[counter] = 0;
		counter++;
	}
	return (temp);
}

//int main()
//{
//    int *arr;
//    size_t size = 5;
//    arr = (int *)calloc(size, sizeof(int));
//    if (arr == NULL)
//        return 1;
//    for (size_t i = 0; i < size; i++)
//        printf("%d ", arr[i]);
//    printf("\n");
//    free(arr);
//    return 0;
//}
