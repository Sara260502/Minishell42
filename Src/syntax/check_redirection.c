/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:07:23 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*controlla se il carattere corrente dell'input corrisponde a un carattere di ridirezione < o >. 
**Se è un carattere di ridirezione, controlla se è presente un carattere successivo che forma una ridirezione doppia (ad es. >> o <<). 
**Restituisce 1 se il carattere corrente corrisponde a una ridirezione, altrimenti restituisce 0.*/
int	ft_check_redir_char(char *line, int i)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<' && line[i - 1] != '<')
			return (1);
		else
			return (1);
	}
	if (line[i] == '>')
	{
		if (line[i + 1] == '>' && line[i - 1] != '>')
			return (1);
		else
			return (1);
	}
	return (0);
}

/* controlla la presenza di caratteri di ridirezione in una riga di input.
** Utilizza ft_check_double_quote e ft_check_single_quote per gestire le citazioni e controllare solo i caratteri fuori dalle citazioni. 
**Se trova una ridirezione doppia, un errore di sintassi viene impostato nel campo error della struttura t_all. Inoltre, se viene trovato un carattere di ridirezione, viene impostato il flag redirections*/
void	ft_check_redirection(char *line, t_all *main)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if ((line[i] == OUTPUT && line[i + 1] == INPUT) || \
			(line[i] == INPUT && line[i + 1] == OUTPUT) || \
			(line[i] == INPUT && line[i + 1] == INPUT && line[i - 1] == INPUT) \
			|| (line[i] == OUTPUT && line[i + 1] == OUTPUT
				&& line[i - 1] == OUTPUT))
			main->error = true;
		if (line[i] == INPUT)
			main->redirections = true;
		if (line[i] == OUTPUT)
			main->redirections = true;
	}
	if (main->error)
		ft_putendl_fd(RED ERROR_OP_LOGIC COLOR_RES, STDOUT_FILENO);
}
