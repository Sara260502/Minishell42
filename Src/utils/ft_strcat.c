/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:32:57 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 12:32:58 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Concatenates two strings.
 *
 * @param dest The destination string.
 * @param src The source string.
 *
 * @returns The destination string.
 */
char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(dest);
	while (*(src + i))
	{
		*(dest + i + j) = *(src + i);
		i++;
	}
	*(dest + i + j) = '\0';
	return (dest);
}
