/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_envi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:56:50 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*aggiunge una variabile d'ambiente alla copia dell'array di stringhe dell'ambiente passato come parametro*/
static char	**ft_add_envi(char *var_add, t_all *main)
{
	int		i;
	char	**tmp;

	i = 0;
	while (main->copy_env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	i = -1;
	while (main->copy_env[++i])
	{
		tmp[i] = ft_strdup(main->copy_env[i]);
		if (!tmp[i])
			break ;
	}
	tmp[i++] = ft_strdup(var_add);
	tmp[i] = NULL;
	ft_free_matrix(main->copy_env);
	return (tmp);
}

/*erifica se la stringa rispetta la sintassi delle variabili d'ambiente*/
int	ft_check_envi(char *line)
{
	int	i;

	i = 1;
	if (ft_isalpha(line[0]) == 0 && line[0] != '_')
		return (0);
	while (line[i] == '_')
		i++;
	while (line[i])
	{
		if (ft_isalnum(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/*richiama ft_add_envi per aggiungere la variabile d'ambiente alla copia dell'array di stringhe dell'ambiente e restituisce il token successivo se presente, altrimenti restituisce il token corrente.*/
t_type	*ft_execute_enviroment(t_type *token, char *var_add)
{
	token->main->copy_env = ft_add_envi(var_add, token->main);
	if (token->next)
		token = token->next;
	return (token);
}
