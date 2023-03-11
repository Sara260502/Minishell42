/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:07:49 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 11:09:06 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*salvare la storia dei comandi inseriti dall'utente in un file di testo. 
**crea una stringa contenente il percorso del file di storia concatenando la variabile d'ambiente HOME e il nome del file di storia. 
**apre il file in modalità append, scrive il comando inserito dall'utente tramite la funzione ft_putendl_fd e chiude il file. 
**Se l'apertura del file fallisce, la funzione termina senza effettuare alcuna operazione.*/
void	ft_add_history(char *line)
{
	int		fd;
	char	*path;
	char	*tmp;

	tmp = getenv("HOME");
	path = ft_strjoin(tmp, FILE_HISTORY);
	fd = open(path, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	free(path);
	add_history(line);
	if (fd < 0)
		return ;
	ft_putendl_fd(line, fd);
	close(fd);
}
