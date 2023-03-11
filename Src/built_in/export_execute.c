/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:37:54 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*stampa sullo standard output tutte le variabili d'ambiente presenti sia in main->copy_env che in main->export_env nel formato "declare -x nome_variabile=valore_variabile".*/
void	ft_export_naked(t_all *main)
{
	int	i;

	i = 0;
	while (main->copy_env[i])
	{
		printf("declare -x %s\n", main->copy_env[i]);
		i++;
	}
	i = 0;
	while (main->export_env[i])
	{
		printf("declare -x %s\n", main->export_env[i]);
		i++;
	}
}

/*duplica la matrice matrix, aggiunge la stringa str come ultima riga della matrice e ritorna il puntatore alla nuova matrice.*/
char	**ft_matrixdup_add(char **matrix, char *str)
{
	char	**new;
	int		i;
	//int		j;

	i = 0;
	//j = 0;
	while (matrix[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	ft_free_matrix(matrix);
	return (new);
}

/*aggiunge la stringa var_add alla matrice main->export_env. 
**Se la stringa è già presente nella matrice, ne modifica il valore corrispondente.*/
void	ft_add_to_exp(char *var_add, t_all *main)
{
	int		j;

	if (ft_find_in_exp(main->export_env, var_add) != 0)
	{
		j = ft_find_in_exp(main->export_env, var_add);
		main->export_env[j] = ft_strdup(var_add);
	}
	else
	{
		j = ft_matrixlen(main->export_env);
		main->export_env = ft_matrixdup_add(main->export_env, var_add);
	}
}

/*aggiunge la stringa var_add alla matrice main->copy_env. Se la stringa è già presente nella matrice, ne modifica il valore corrispondente.*/
void	ft_add_to_env(char *var_add, t_all *main)
{
	int		j;

	if (ft_find_in_env(main->copy_env, var_add) != 0)
	{
		j = ft_find_in_env(main->copy_env, var_add);
		main->copy_env[j] = ft_strdup(var_add);
	}
	else
	{
		j = ft_matrixlen(main->copy_env);
		main->copy_env = ft_matrixdup_add(main->copy_env, var_add);
	}
}

/*gestisce il comando export dell'interprete di comandi minishell. 
**Se non sono specificate opzioni, richiama la funzione ft_export_naked per stampare tutte le variabili d'ambiente presenti. 
**Altrimenti, analizza ogni opzione (che deve essere nel formato "nome_variabile=valore_variabile"), e se il nome della variabile è valido (ovvero rispetta le convenzioni per i nomi delle variabili d'ambiente), la aggiunge alla matrice main->copy_env. 
**Altrimenti, se la stringa non rispetta le convenzioni, stampa un messaggio di errore.*/
void	ft_export(t_type *token, t_all *main)
{
	int	i;
	//int	j;

	//j = 0;
	i = 1;
	if (token->value[1] == NULL)
		return (ft_export_naked(main));
	while (token->value[i])
	{
		if (ft_strchr(token->value[i], '=') == 0
			|| ft_check_envi(token->value[i]) == 0)
		{
			if (ft_check_envi(token->value[i]) == 0)
				printf(RED"minishell: export: '%s': not a valid identifier\n"
					COLOR_RES, token->value[i]);
			else
				ft_add_to_exp(token->value[i], main);
			i++;
			continue ;
		}
		ft_add_to_env(token->value[i], main);
		i++;
	}
}
