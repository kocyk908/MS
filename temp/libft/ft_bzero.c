/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruszkie <pruszkie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/03/11 16:23:43 by pruszkie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

//int main() {
//    int numbers[5] = {1, 2, 3, 4, 5};
//    size_t size_numbers = sizeof(numbers);

//    printf("Original:\n");
//    for (size_t i = 0; i < size_numbers / sizeof(int); ++i) {
//        printf("%d ", numbers[i]);
//    }
//    printf("\n");

//    ft_bzero(numbers, size_numbers);

//    printf("After:\n");
//    for (size_t i = 0; i < size_numbers / sizeof(int); ++i) {
//        printf("%d ", numbers[i]);
//    }
//    printf("\n");

//    return 0;
//}
