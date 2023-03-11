/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:07:01 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla se una data stringa ha una coppia di virgolette doppie (" "). Se la stringa ha almeno una virgoletta doppia, incrementa il contatore dub_quotes nella struttura t_all. 
**In caso contrario, la funzione restituisce l'indice corrente della stringa.*/
int	ft_check_double_quote(char *line, t_all *main, int i)
{
	if (line[i] == '"')
	{
		main->dub_quotes++;
		i++;
		while (line[i])
		{
			if (line[i] == '"' && line[i - 1] != 92)
			{
				main->dub_quotes++;
				break ;
			}
			i++;
		}
	}
	return (i);
}
