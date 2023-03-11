/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:30:51 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*stampa i valori dei token a partire dal secondo. Se il secondo token è "-n", non viene stampata alcuna riga vuota alla fine.*/
void	ft_echo(t_type *token)
{
	int		i;

	i = 1;
	if (!token->value[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(token->value[1], "-n") != 0)
		i++;
	while (token->value[i])
	{	
		printf("%s", token->value[i]);
		if (token->value[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(token->value[1], "-n") == 0)
		printf("\n");
}

/*controlla se il token corrente ha una condizione OR precedente. 
**Se non ha una condizione OR precedente, viene chiamata ft_echo per stampare il token*/
void	ft_echo_or(t_type *token)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				;
		}
	}
	else
		ft_echo(token);
}

/* esegue il trim di una stringa line a partire dalla posizione i, utilizzando il carattere trim come carattere di riferimento.
**I caratteri della stringa da eliminare vengono sostituiti con il carattere 127. 
**La funzione restituisce la posizione dell'ultimo carattere della stringa line dopo il trim.*/
static int	ft_oppost_trim(char *line, int i, char trim)
{
	char	quot;

	quot = line[i];
	if (ft_strchr(&line[i], trim))
		line[i] = 127;
	while (line[i] != quot)
		i++;
	if (line[i] == quot)
		line[i] = 127;
	return (i);
}

/*labora i valori dei token per gestire correttamente le virgolette singole e doppie*/
static void	ft_preparet_echo(t_type *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (token->value[++i])
	{
		j = -1;
		if (ft_strnstr(token->value[i], "-n", 2))
			token->value[i] = ft_check_echo_n(token->value[i]);
		while (token->value[i][++j])
		{
			if (token->value[i][j] == '\'')
				j = ft_oppost_trim(token->value[i], j, '"');
			else if (token->value[i][j] == '"')
				j = ft_oppost_trim(token->value[i], j, '\'');
		}
		tmp = ft_strtrim2(token->value[i], 127);
		token->value[i] = ft_strdup(tmp);
	}
}

/*controlla se il token ha una condizione OR o AND precedente e, a seconda di ciò, chiama la funzione ft_echo o ft_echo_or o termina il programma.*/
void	ft_check_echo(t_type *token)
{
	ft_preparet_echo(token);
	if (token->prev)
	{
		if (token->prev->or)
			ft_echo_or(token);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_echo(token);
		}
		else
			ft_echo(token);
	}
	else
		ft_echo(token);
}
