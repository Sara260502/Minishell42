/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_priority.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:05:59 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*prende in input una stringa e restituisce un array di sottostringhe. 
**Viene utilizzata per sostituire i caratteri delimitatori specifici (38, 59, 124) con un carattere non utilizzato (127) in modo da dividere correttamente la stringa in sottostringhe. 
**vengono rimossi i singoli e doppi apici (utilizzati per le stringhe tra virgolette) e viene restituito l'array di sottostringhe risultante.*/
char	**ft_utils_set_priority(char *line, t_all *main)
{
	int		i;
	char	*dup;
	char	**rtr;

	i = 0;
	dup = ft_strdup(line);
	while (dup[i])
	{
		i = ft_check_single_quote(dup, main, i);
		i = ft_check_double_quote(dup, main, i);
		if (dup[i] != 38 && dup[i] != 59 && dup[i] != 124)
			i++;
		else if (dup[i])
		{
			dup[i] = 127;
			i++;
		}
	}
	rtr = ft_split_original(dup, 127);
	free(dup);
	return (rtr);
}

/*Controlla la presenza di apici singoli e doppi all'interno di una singola sottostringa.*/
static int	ft_support_priority(char **tmp, t_all	*main, int i, int j)
{
	j = ft_check_double_quote(tmp[i], main, j);
	j = ft_check_single_quote(tmp[i], main, j);
	return (j);
}

/*Questa funzione prende in input la stringa di input, un puntatore alla struttura t_all (che contiene una lista di token) e un valore di parentesi(bracke). 
**suddivide la stringa di input in sottostringhe utilizzando la funzione ft_utils_set_priority.
**esamina ogni sottostringa e assegna un valore di priorità ai token all'interno di ogni sottostringa in base alla presenza di parentesi. 
**In particolare, la variabile brack viene incrementata quando viene trovata una parentesi aperta e decrementata quando viene trovata una parentesi chiusa. 
**Il valore di brack viene poi assegnato come valore di priorità al token corrente.*/
void	ft_set_priority(char *line, t_all *main, int brack)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	tmp = ft_utils_set_priority(line, main);
	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
		{
			j = ft_support_priority(tmp, main, i, j);
			if (tmp[i][j] == '(')
				brack++;
			main->token->priority = brack;
			if (tmp[i][j] == ')')
			{
				brack--;
				break ;
			}
		}
		if (main->token->next)
			main->token = main->token->next;
	}
	ft_free_matrix(tmp);
}
