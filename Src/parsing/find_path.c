/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:05:28 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 14:00:12 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*cerca la posizione dell'ambiente PATH all'interno di una copia dell'ambiente principale main->copy_env
**restituisce l'indice in cui si trova. Se non viene trovato, viene impostata la variabile globale g_exit a 127 e viene restituito 1*/
static int	ft_exceptions_path(t_all *main)
{
	int	len;
	int	i;

	i = 0;
	len = ft_matrixlen(main->copy_env);
	while (main->copy_env[i])
	{
		if (!(ft_strncmp("PATH=", main->copy_env[i], 5)))
			break ;
		i++;
	}
	if (i >= len)
	{
		g_exit = 127;
		return (1);
	}
	return (i);
}

/*rende come argomenti una stringa cmd che rappresenta il comando da cercare e una stringa paths che rappresenta una directory del percorso di ricerca PATH. 
**La funzione unisce la directory paths con il comando cmd per creare il percorso completo e lo restituisce.*/
static char	*ft_support_path(char *cmd, char *paths)
{
	char	*rtr;
	char	*part_path;

	part_path = ft_strjoin(paths, "/");
	rtr = ft_strjoin(part_path, cmd);
	free(part_path);
	return (rtr);
}

/*cerca il percorso completo del comando cmd utilizzando le directory del percorso di ricerca PATH. 
**La funzione controlla prima se cmd è già un percorso completo, nel qual caso lo restituisce direttamente. 
**Se invece cmd non contiene il percorso completo, la funzione cerca il percorso completo del comando utilizzando le directory del percorso di ricerca PATH. 
**Viene utilizzata la funzione access per controllare se il percorso completo è valido. 
**Se il percorso viene trovato, la funzione restituisce il percorso completo, altrimenti restituisce NULL.*/
char	*ft_find_path(char *cmd, t_all *main)
{
	char	**paths;
	char	*right_path;
	int		i;

	i = ft_exceptions_path(main);
	if (i == 1)
		return (NULL);
	if (ft_strnstr(cmd, "/bin/", ft_strlen(cmd)))
		return (ft_strdup(cmd));
	paths = ft_split(main->copy_env[i] + 5, ":");
	i = -1;
	while (paths[++i])
	{
		right_path = ft_support_path(cmd, paths[i]);
		if (access(right_path, F_OK) == 0)
		{
			ft_free_matrix(paths);
			return (right_path);
		}
		free(right_path);
	}
	ft_free_matrix(paths);
	return (NULL);
}
