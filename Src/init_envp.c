/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:08:00 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 11:09:06 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*La variabile d'ambiente SHLVL (shell level) indica il livello di profondità della shell corrente rispetto alla shell di login e viene utilizzata per tenere traccia del numero di volte in cui una shell è stata avviata all'interno della shell principale. 
**Ad esempio, quando si avviano altre shell all'interno della shell principale, il valore di SHLVL aumenta di uno per ogni shell aggiuntiva. 
**Questa variabile viene utilizzata per evitare loop infiniti o per controllare il comportamento di uno script all'interno di una shell annidata.*/

/*incrementa il valore di SHLVL nell'array di stringhe copy_envp copiando l'elemento corrispondente da envp*/
void	ft_change_shlvl(char **copy_envp, char *str, int index)
{
	int		num;
	char	*num_str;

	num = 0 + (str[6] - '0');
	num_str = ft_itoa(num + 1);
	copy_envp[index] = ft_strjoin("SHLVL=", num_str);
	free(num_str);
}

/*aggiunge alcune variabili d'ambiente all'array copy_envp*/
void	ft_add_shell_env(char **copy_envp, char **envp, int i)
{
	char	*tmp;
	char	*tmp2;

	copy_envp[i++] = ft_strdup("HISTSIZE=2000");
	tmp = ft_searchstrchr("HOME=", envp);
	tmp2 = ft_strjoin("HISTFILE=", tmp);
	copy_envp[i++] = ft_strjoin(tmp2, FILE_HISTORY);
	free(tmp);
	free(tmp2);
	copy_envp[i] = NULL;
}

/*crea una copia dell'array envp, incrementando il valore di SHLVL e aggiungendo altre variabili d'ambiente attraverso le due funzioni precedenti*/
char	**ft_init_envp(char **envp)
{
	int		i;
	char	**copy_envp;

	i = 0 ;
	while (envp[i])
		i++;
	copy_envp = malloc(sizeof(char *) * (i + 3));
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("SHLVL=", envp[i], 6))
			ft_change_shlvl(copy_envp, envp[i], i);
		else if (!ft_strncmp("SHELL=", envp[i], 5))
			copy_envp[i] = ft_strdup("SHELL=42minishell");
		else
		{
			copy_envp[i] = ft_strdup(envp[i]);
			if (copy_envp[i])
				continue ;
			ft_free_matrix(copy_envp);
			exit(127);
		}				
	}
	ft_add_shell_env(copy_envp, envp, i);
	return (copy_envp);
}
