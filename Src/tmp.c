/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:08:12 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*prende in input un puntatore alla testa di una lista di token t_type e stampa su stdout le informazioni contenute in ogni nodo della lista
** ovvero il comando, i suoi valori, il nome del file associato, la priorità e i vari flag booleani che indicano la presenza di un token specifico come and, or, pipe, output, append, input, heredoc. 
**attraversa la lista stampando le informazioni di ogni nodo finché non arriva all'ultimo elemento.*/
void	ft_print_lst(t_type *token)
{
	int		i;
	t_type	*a;

	a = token;
	while (a)
	{
		printf("%s --- Comand\n", a->command);
		i = -1;
		while (a->value[++i] != NULL)
			printf("%s --- Value %d\n", a->value[i], i);
		printf("%s -- Token Name File\n", a->name_file);
		printf("%d -- Priority\n", a->priority);
		printf("%d -- Bool Res\n", a->res);
		printf("%d -- Bool And\n", a->and);
		printf("%d -- Bool Or\n", a->or);
		printf("%d -- Bool Pipe\n", a->pipe);
		printf("%d -- Bool Output\n", a->output);
		printf("%d -- Bool Append\n", a->append);
		printf("%d -- Bool Input\n", a->input);
		printf("%d -- Bool Heredoc\n", a->heredoc);
		if (!a->next)
			break ;
		a = a->next;
	}
}
