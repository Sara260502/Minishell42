/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:34:34 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 12:34:39 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		l;
	char				*str;
	unsigned int		i;

	if (!s)
		return (NULL);
	l = ft_strlen((char *)s);
	if (l < len)
		str = (char *)malloc(l * sizeof(char) + 1);
	else
		str = (char *)malloc(len * sizeof(char) + 1);
	i = 0;
	if (str == NULL)
		return (NULL);
	while (i <= l && len > 0 && start <= l)
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}
