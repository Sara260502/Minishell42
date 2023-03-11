/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:06:13 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*restituisce il puntatore al primo elemento di una lista a doppia direzione.*/
t_type	*ft_return_head(t_type *list)
{
	while (list)
	{
		if (!list->prev)
			break ;
		list = list->prev;
	}
	return (list);
}

/*supporta il parsing della linea di comando eseguendo alcune operazioni come la rimozione di singole e doppie virgolette e il salto tra parentesi.*/
int	ft_support_parsing(char *line, t_all *main, int i)
{	
	i = ft_check_single_quote(line, main, i);
	i = ft_check_double_quote(line, main, i);
	i = ft_jump_brackets(line, i);
	return (i);
}

/*conta il numero di elementi in un array di stringhe suddividendo la stringa in base agli spazi e alle virgolette singole o doppie.*/
int	ft_count_array(char *line, t_all *main)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
			count++;
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] != 32 && line[i - 1] == 32)
			count++;
		i++;
	}
	return (count);
}
