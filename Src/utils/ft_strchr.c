/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:33:02 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 12:33:08 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strchr(const char *s, int c)
{
	size_t	i;
	char	let;

	i = 0;
	let = c;
	while (s[i] != let && s[i] != '\0')
		i++;
	if (s[i] == let)
		return (1);
	return (0);
}

int	ft_strchr_until(const char *s, int c)
{
	size_t	i;
	char	let;

	i = 0;
	let = c;
	while (s[i] != let && s[i] != '\0')
		i++;
	if (s[i] == let)
		return (i);
	return (0);
}
