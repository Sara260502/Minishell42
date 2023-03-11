/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:47:15 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*cerca una variabile d'ambiente all'interno della matrice matrix e restituisce l'indice in cui viene trovata*/
int	ft_find_in_env(char **matrix, char *str)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], str, ft_strchr_until(str, '=')) == 0)
			return (i);
		i++;
	}
	return (0);
}

/*fa la stessa cosa, ma cerca una variabile d'esportazione.*/
int	ft_find_in_exp(char **matrix, char *str)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], str, (ft_strlen(str))) == 0)
			return (i);
		i++;
	}
	return (0);
}

/*controlla se la stringa contenuta nel primo elemento del token corrente è un comando builtin, ovvero un comando interno del nostro shell*/
int	ft_check_builtin(t_type *token)
{
	if (ft_strcmp(token->value[0], "exit") || ft_strcmp(token->value[0], "env") \
	|| ft_strcmp(token->value[0], "unset") || ft_strcmp(token->value[0], "pwd") \
	|| ft_strcmp(token->value[0], "cd") || ft_strcmp(token->value[0], "echo") \
	|| ft_strcmp(token->value[0], "export"))
		return (1);
	return (0);
}

/*controlla se la stringa passata come argomento inizia con la lettera "n" e, in tal caso, restituisce una stringa che rappresenta l'opzione -n del comando echo*/
char	*ft_check_echo_n(char *str)
{
	size_t		i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (i < ft_strlen(str))
		return (str);
	else
		return ("-n");
}
