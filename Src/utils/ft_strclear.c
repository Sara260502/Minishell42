/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:33:19 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 12:33:20 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strclear(char *str, char del)
{
	int		i;
	int		count;
	char	*rtr;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != del)
			count++;
	}
	rtr = (char *)malloc(sizeof(char) * count);
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] != del)
			rtr[count++] = str[i];
	}
	if (rtr)
	{
		rtr[count++] = '\0';
		return (rtr);
	}
	return (NULL);
}
