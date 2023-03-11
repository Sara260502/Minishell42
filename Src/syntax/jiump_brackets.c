/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jiump_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:07:32 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 11:09:06 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*permette di saltare all'interno di una coppia di parentesi tonde. Viene utilizzata per la gestione degli argomenti di una funzione.*/
int	ft_jump_brackets(char *line, int i)
{
	if (line[i] == 28)
	{
		i++;
		while (line[i])
		{
			if (line[i] == 29)
				break ;
			i++;
		}
	}
	return (i);
}

/*controlla se una variabile d'ambiente deve essere espansa. 
**Verifica se il carattere precedente o successivo è un simbolo del dollaro, se la lunghezza della stringa è 1 e se ci sono un numero dispari di apici doppi. 
**In caso affermativo, ritorna 1, altrimenti 0.*/
int	ft_check_expand(char *line, int i)
{
	bool	dollar;
	int		count;

	dollar = FALSE;
	count = 1;
	if (line[i] == '$')
		dollar = TRUE;
	else
		return (0);
	if (((line[i + 1] == '$' || line[i - 1] == '$') && dollar) \
			|| ft_strlen(line) == 1)
		return (0);
	while (i > 0)
	{
		if (line[i] == '"')
			count++;
		i--;
	}
	if ((count % 2) == 0 && !ft_strchr(line, '"'))
		return (0);
	if (dollar)
		return (1);
	return (0);
}
