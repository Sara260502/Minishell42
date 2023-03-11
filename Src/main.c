/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:08:04 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*esegue il loop principale che continua fino a quando il programma viene terminato manualmente. 
**la funzione ottiene la directory home dell'utente tramite la variabile d'ambiente "HOME", imposta la directory corrente di lavoro e richiama la funzione ft_prompt che visualizza la riga di comando dell'utente. 
**la funzione libera la memoria allocata per la struttura t_type e per la directory corrente di lavoro.*/
void	ft_loop(t_all *main)
{
	char	*tmp;

	tmp = getenv("HOME");
	main->files_pwd = ft_strjoin(tmp, "/");
	main->token = (t_type *)malloc(sizeof(t_type));
	if (!main->token)
		return ;
	ft_prompt(main);
	free(main->token);
	free(main->files_pwd);
}

/*nizializza la struttura t_all, la variabile globale g_exit, l'ambiente copiato main->copy_env e l'array per le variabili di esportazione main->export_env. 
**Imposta i segnali SIGINT e SIGQUIT. Infine, esegue il loop principale chiamando la funzione ft_loop finché il programma viene terminato. 
**Alla fine del loop, viene liberata la memoria allocata per l'ambiente copiato*/
int	main(int argc, char **argv, char **envp)
{
	t_all	*main;

	(void)argc;
	(void)argv;
	g_exit = 0;
	main = (t_all *)malloc(sizeof(t_all));
	if (!main)
		return (0);
	main->copy_env = ft_init_envp(envp);
	main->export_env = malloc (sizeof(char **) * 1);
	if (!main->export_env)
	{
		ft_free_matrix(main->copy_env);
		return (0);
	}
	main->export_env[0] = NULL;
	signal(SIGINT, ft_sig_handel);
	signal(SIGQUIT, ft_sig_handel);
	while (1)
		ft_loop(main);
	ft_free_matrix(main->copy_env);
}
