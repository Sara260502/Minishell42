/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:34:24 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 12:34:28 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strtrim3(char *str, char *del)
{
	int		i;
	char	**matrix;
	char	*rtr;

	i = 0;
	matrix = ft_split_original(del, 32);
	while (1)
	{
		rtr = ft_strtrim2(str, matrix[i][0]);
		if (!ft_strchr(str, matrix[i][0]))
		{
			i++;
			if (!matrix[i])
				break ;
		}
		str = ft_strdup(rtr);
		free(rtr);
	}
	ft_free_matrix(matrix);
	return (rtr);
}
