/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:06:08 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*suddivide una riga di input in token separati e li assegna a una struttura t_type. 
**Analizza la riga carattere per carattere, sostituendo gli spazi e le parentesi chiuse con un carattere non stampabile (127). 
**Quindi usa la funzione ft_split_original per dividere la riga in token separati da questo carattere, e li assegna ai membri value della struttura t_type*/
static void	ft_divide_line(char *line, t_type *token, t_all *main)
{
	int		i;
	char	**tmp;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == 32 || line[i] == ')')
			line[i] = 127;
	}
	tmp = ft_split_original(line, 127);
	i = 0;
	while (tmp[i])
	{
		token->value[i + 1] = ft_strdup(tmp[i]);
		i++;
	}
	token->value[i + 1] = NULL;
	ft_free_matrix(tmp);
}

/*elabora il valore del token command per rimuovere eventuali citazioni singole o doppie. 
**cerca il percorso del comando specificato usando la funzione ft_find_path (non mostrata qui), che cerca il percorso completo di un eseguibile a partire dalla variabile d'ambiente PATH. 
**elabora il valore del token per rimuovere eventuali citazioni rimaste.*/
static void	ft_trimming(t_all *main, t_type *token, int i)
{
	char	*tmp;

	token->value[i] = ft_strdup(token->command);
	free(token->command);
	token->command = ft_find_path(token->value[i], main);
	tmp = ft_strtrim2(token->value[i], '"');
	free(token->value[i]);
	token->value[i] = ft_strtrim2(tmp, '\'');
	free(tmp);
}

/*analizza un'input dell'utente suddividendolo in token separati e assegnando valori appropriati ai token*/
void	ft_set_values(char **line, t_all *main)
{
	int		j;
	int		i;
	t_type	*token;

	token = ft_return_head(main->token);
	j = 0;
	i = 0;
	while (token)
	{
		token->value = (char **)malloc(sizeof(char *) * \
							(ft_count_array(line[j], main) + 2));
		if (!token->value)
			return ;
		ft_trimming(main, token, i);
		ft_divide_line(line[j], token, main);
		if (token->next)
			token = token->next;
		else
			break ;
		j++;
	}
}
