/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:06:54 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:47:51 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*gestisce le ridirezioni di input/output di un token. 
**Controlla il tipo di ridirezione e chiama le funzioni appropriate, elimina le ridirezioni, ripristina l'uscita standard se necessario e poi esegue il comando del token.*/
void	ft_single_redir(t_type *token, t_all *main)
{
	if (token->heredoc == 1)
		ft_heredoc(token, main);
	if (token->output == 1 || token->append == 1)
		ft_output_redirect(token, main);
	if (token->input == 1)
		ft_input_redirect(token);
	ft_delete_redirection(token);
	if (token->command == NULL)
	{
		if (token->stdoutput != STDOUT_FILENO)
			dup2(token->dup, STDOUT_FILENO);
		else if (token->stdinput != STDIN_FILENO)
			dup2(token->dup, STDIN_FILENO);
	}
	ft_execute_redi(token, main);
}

/*sostituisce il carattere '>' e '<' con il carattere ASCII 127 per indicare che questi caratteri sono da eliminare dalla stringa.*/
char	*ft_set_to_del(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			line[i] = 127;
		i++;
	}
	return (line);
}

/*elimina il carattere 127 dalle stringhe della matrice di stringhe passata come argomento.*/
char	**ft_clear_matrix(char **matrix)
{
	int		i;
	char	*tmp;

	i = 1;
	while (matrix[i])
	{
		tmp = ft_strdup(matrix[i]);
		free(matrix[i]);
		matrix[i++] = ft_strtrim2(tmp, 127);
		free(tmp);
	}
	return (matrix);
}

/*onta quante ridirezioni di output ci sono nel token.*/
int	ft_count_redirection(t_type *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (ft_strcmp(token->value[i], ">") \
			|| ft_strcmp(token->value[i], ">>"))
			count++;
		i++;
	}
	return (count);
}
