/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:05:16 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla se una linea di comando contiene le parentesi graffe in modo corretto
**restitisce TRUE se c'è un errore di formattazione e FALSE altrimenti.*/
static bool	ft_support(char *line, int i, bool error) 
{
	if (line[++i] == '{')
	{
		while (line[++i] != 32 && line[i])
		{
			if (line[i] == '}')
			{
				error = FALSE;
				break ;
			}
		}
	}
	else
		error = FALSE;
	return (error);
}

/*cerca il carattere '$' nella stringa di input e, se lo trova, controlla che le parentesi graffe in quel punto siano formattate correttamente*/
bool	ft_expand_check(char *line)
{
	int		i;
	bool	error;

	i = 0;
	error = TRUE;
	while (line[i] != '$')
		i++;
	error = ft_support(line, i, error);
	if (error)
	{
		ft_putendl_fd(RED ERROR_CLOSE_ COLOR_RES, STDOUT_FILENO);
		return (TRUE);
	}
	return (FALSE);
}

/*esegue la sostituzione delle variabili in una stringa di input in cui è presente il carattere '$'. 
**Controlla anche se la variabile è racchiusa tra apici doppi, nel qual caso non viene eseguita la sostituzione.*/
void	ft_execute_dollar(t_type *token, t_all *main)
{
	int		i;
	int		j;
	int		doub_quot;

	i = 0;
	j = 0;
	doub_quot = 0;
	while (token->value[i])
	{
		j = 0;
		while (token->value[i][j])
		{
			if (token->value[i][j] == '"')
				doub_quot++;
			if (doub_quot % 2 == 0)
				j = ft_check_single_quote(token->value[i], main, j);
			if (ft_check_expand(token->value[i], j))
				token->value[i] = ft_expand_doll(token->value[i], main, j + 1);
			j++;
		}
		i++;
	}
}

/* cerca il carattere '$' nella stringa di input e sostituisce il valore della variabile corrispondente se presente. 
**La variabile viene individuata a partire dal carattere successivo a '$'
**termina quando viene incontrato uno spazio, un apice singolo o un apice doppio. Restituisce la stringa di input con la sostituzione effettuata.*/
char	*ft_expand_heredoc(char *line, t_all *main)
{
	int	i;
	int	l;
	int	start;

	i = 0;
	l = 0;
	start = 0;
	while (line[i] != '$' )
		i++;
	if (line[i] == '$')
		start = i + 1;
	while (line[++i] && line[i] != ' ' && line[i] != '"')
		l++;
	if (start != 0)
		line = ft_change_var_in_dollar(start, l, line, main);
	return (line);
}
