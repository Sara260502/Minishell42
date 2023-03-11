/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:34:43 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 12:34:44 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_get_next_line(int fd, char *file)
{
	int		i;
	char	c;
	char	**rtr;
	char	*buffer;

	i = 0;
	buffer = malloc (9999);
	fd = open(file, O_CREAT | O_RDONLY, 0644);
	while (read(fd, &c, 1) > 0)
	{
		buffer[i] = c;
		i++;
		if (c == '\0')
			break ;
	}
	close(fd);
	buffer[i] = '\0';
	rtr = ft_split_original(buffer, '\n');
	free(buffer);
	free(file);
	return (rtr);
}
