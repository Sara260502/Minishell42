/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:08:08 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:46:26 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*gestisce i segnali SIGINT e SIGQUIT. 
**Nel primo caso, stampa una nuova riga e poi ripristina la riga di input a vuota usando le funzioni della libreria readline. 
**Nel secondo caso, torna all'inizio della riga di input.*/
void	ft_sig_handel(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

/*setta la modalità del terminale in modo che il testo digitato non venga mostrato (usando tcgetattr e tcsetattr) e quindi usa la funzione readline della libreria readline per ottenere l'input dell'utente. 
**Infine, ripristina la modalità del terminale originale.*/
char	*ft_set_term(char *name_shell)
{
	struct termios	new;
	struct termios	old;
	char			*rtr;	

	if (tcgetattr(STDIN_FILENO, &old))
		perror("tcgetattr1");
	new = old;
	new.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &new))
		perror("tcsetattr2");
	rtr = readline(name_shell);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &old))
		perror("tcsetattr3");
	free(name_shell);
	return (rtr);
}

/*rimuove il percorso della directory corrente dal prompt*/
char	*ft_clear_prompt(char *prompt)
{
	char	*rtr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (prompt[i] != '\0')
		i++;
	while (prompt[i - j] != '/')
		j++;
	j--;
	rtr = ft_substr(prompt, i - j, ft_strlen(prompt));
	free(prompt);
	return (rtr);
}

/*crea il prompt utilizzando la directory corrente dell'utente e il nome della shell. 
**ottiene la directory corrente usando la funzione getcwd della libreria unistd. 
**Verifica se la directory corrente è la stessa della home dell'utente e costruisce il prompt in base a questo.*/
char	*ft_get_line_input(void)
{
	char	*prompt;
	char	*tmp;
	char	*home;
	char	*pwd;

	home = getenv("HOME");
	pwd = getcwd(NULL, 0);
	if (ft_strcmp(home, pwd))
		prompt = ft_strjoin(pwd, HOME_SHELL);
	else
		prompt = ft_strjoin(pwd, DIVISOR_SHELL);
	free(pwd);
	tmp = ft_clear_prompt(prompt);
	prompt = ft_strjoin(NAME_SHELL, tmp);
	free(tmp);
	prompt = ft_set_term(prompt);
	return (prompt);
}

/*gestisce l'intero prompt dell'applicazione. Richiama la funzione ft_get_line_input per ottenere l'input dell'utente e quindi verifica se l'input è nullo. 
**Se l'input non è nullo, la funzione aggiunge la linea alla cronologia degli input (usando la funzione ft_add_history della libreria readline) e controlla la sintassi della linea (usando la funzione ft_check_syntax). 
**Se la sintassi è corretta, la funzione suddivide la linea in token (usando la funzione ft_parsing) e poi esegue il comando corrispondente (usando la funzione ft_execute_command). Infine, libera la memoria allocata per i token e la copia della linea di input.*/
int	ft_prompt(t_all *main)
{
	char	*line;

	line = ft_get_line_input();
	if (!line)
	{
		printf(RED "\texit\n" COLOR_RES);
		free(main->files_pwd);
		free(main->token);
		exit(127);
	}
	else if (line[0] != '\0')
	{
		ft_add_history(line);
		ft_check_syntax(line, main);
		if (!main->error)
		{
			ft_parsing(line, main);
			ft_execute_command(main);
			ft_free_token(main->token);
			free(main->copy_line);
		}
	}
	free(line);
	return (0);
}
