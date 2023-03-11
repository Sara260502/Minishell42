/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/8 10:28:49 by sarazicchie       #+#    #+#             */
/*   Updated: 2023/03/11 13:59:11 by sarazicchie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <curses.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h> 

# define NAME_SHELL "\033[0;36m\033[1mminishell42 ▸ \x1b[0m"
# define DIVISOR_SHELL " ▸ "
# define HOME_SHELL " ~ "
# define FILE_HISTORY "/.minishell42_history"
# define RED "\x1b[31m"
# define COLOR_RES  "\x1b[0m"
# define ERROR_DOUBLE_QUOTE "Mistake : unclosed double quotes"
# define ERROR_SING_QUOTE "Mistake : unclosed single quotes"
# define ERROR_BACKSLASH "Mistake : find the '\\'"
# define ERROR_OPEN_BRACKETS "Mistake : find open brackets exstra"
# define ERROR_CLOSE_BRACKETS "Mistake : find close brackets exstra"
# define ERROR_CLOSE_ "Mistake : bad substitution"
# define ERROR_OP_LOGIC "Syntax error near unexpected token"
# define ERROR_FILE "No such file or directory"
# define ERROR_EXIT "Exit"
# define INPUT 60
# define OUTPUT 62

typedef struct s_type
{
	int				res; //risultato esecuzione 
	int				priority; //priorità di esecuzione del comando
	int				dup; //indica se token è duplicato o meno
	int				stdinput; //indica se l'input è stato preso dallo stdin
	int				stdoutput; //indica se l'output è stato scritto sullo stdout
	char			**value; //puntatore ad una lista di stringhe che rappresentano i valori dei token
	char			*command; //rappresenta comando dei token
	char			*name_file; //nome file associato al token
	bool			or; // indica se il token rappresenta l'operatore OR
	bool			and; // operatore AND
	bool			pipe; //indica se token rappresenta una pipe
	bool			input; //indica se token rappresenta un'operazione di input
	bool			output; // operazione output
	bool			append; //se il token rappresenta un'operazione di append
	bool			heredoc; // operazione di heredoc 
	struct s_all	*main; //puntatore alla struttura t_all
	struct s_type	*next; //token successivo
	struct s_type	*prev; //token precedente
}	t_type;

typedef struct s_all
{
	char		**copy_env; //puntatore a lista stringhe che rappresentano variabili d'ambiente copiate 
	char		**export_env; //variabili esportate
	char		*files_pwd; //rappresenta il percorso della directory corrente
	char		*copy_line; //rappresenta la riga di comando copiata
	int			open_brackets; //numero di parentesi aperte
	int			close_brackets; //num parentesi chiuse
	int			fd_matrix; //matrice di descrittori di file
	int			fd_export; //file descriptor di esportazione
	int			dub_quotes; //numero di virgolette doppie trovate
	int			sin_quotes; //numero di virgolette singole trovate
	int			count; //conteggio
	bool		op_logic; //ndica se il programma ha operatori logici
	bool		error;
	bool		redirections; //indica se il programma ha operazioni di ridirezione
	bool		expand; //indica se la linea di comando deve essere estesa
	t_type		*token; //puntatore alla struttura t_type
}	t_all;

// Global
int	g_exit;

extern void	rl_replace_line(const char *text, int clear_undo);

// DIR Utils
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strchr(const char *s, int c);
int			ft_strchr_until(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_lstsize(t_type *lst_or);
int			ft_lstsize_this(t_type *lst_or);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_searchstrchr(char const *str, char **array);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char *charset);
char		**ft_split_original(char const *s, char c);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strdup(const char *s1);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_type **lst, t_type *new);
void		ft_lstcopy(t_type **lst, t_type *new);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strtrim(char const *s1, char const *set);
t_type		*ft_lstnew(void *content, t_all *main);
size_t		ft_strlen(char *s);
size_t		ft_matrixlen(char **s);
int			ft_find_in_env(char **matrix, char *str);
int			ft_find_in_exp(char **matrix, char *str);
char		**ft_get_next_line(int fd, char *file);
char		*ft_strcpy(char *dst, char *src);
char		*ft_strclear(char *str, char del);
char		*ft_strtrim2(char *str, char del);
void		ft_print_matrix(char **matrix);
char		*ft_strtrim3(char *str, char *del);

/*free.c*/
void		ft_free_matrix(char **matrix);
void		ft_free_token(t_type *token);

/*init_envp.c*/
char		**ft_init_envp(char **envp);

/*prompt.c*/
int			ft_prompt(t_all *main);
void		ft_sig_handel(int signal);

/*history.c*/
void		ft_add_history(char *line);

/*DIR syntax_check*/
int			ft_check_single_quote(char *line, t_all *main, int i);
int			ft_check_double_quote(char *line, t_all *main, int i);
int			ft_check_expand(char *line, int i);
int			ft_jump_brackets(char *line, int i);
int			ft_check_redir_char(char *line, int i);
void		ft_check_syntax(char *line, t_all *main);
void		ft_check_redirection(char *line, t_all *main);

/*DIR Execute*/
int			ft_check_envi(char *line);
void		ft_execute_command(t_all *main);
void		ft_store_matrix(t_all *main);
void		ft_execute_redi(t_type *token, t_all *main);
void		ft_start_execute_(t_all *main);
void		ft_parent_execute_(t_type *token, pid_t pidchild, int fd_pipe[2]);
t_type		*ft_execute_enviroment(t_type *token, char *var_add);
t_type		*ft_execute_exeve(t_type *token, t_all *main);

/*DIR Parsing*/
int			ft_count_array(char *line, t_all *main);
int			ft_support_parsing(char *line, t_all *main, int i);
char		*ft_find_path(char *cmd, t_all *main);
char		*ft_find_token(char *line, t_all *main, bool first);
void		ft_parsing(char *line, t_all *main);
void		ft_set_op_logic(char *line, t_type *token);
void		ft_set_values(char **line, t_all *main);
void		ft_set_priority(char *line, t_all *main, int brack);
void		ft_set_redirections(t_type *token);
void		ft_set_info(char **tmp, t_all *main, char *copy_line, int count);
void		ft_check_dir(t_all *main);
t_type		*ft_return_head(t_type *list);

/*DIR Built_in*/
int			ft_check_builtin(t_type *token);
char		*ft_check_echo_n(char *str);
void		ft_check_echo(t_type *token);
void		ft_check_export(t_type *token, t_all *main);
void		ft_check_cd(t_type *token, t_all *main);
void		ft_check_pwd(t_type *token);
void		ft_check_env(t_type *token, t_all *main);
void		ft_check_unset(t_type *token, t_all *main);
void		ft_export(t_type *token, t_all *main);
void		ft_check_exit(t_type *token);
void		ft_export(t_type *token, t_all *main);
void		ft_exit(t_type *token);
t_type		*ft_execute_builtin(t_type *s_type, t_all *main);
t_type		*ft_end_execute_(t_type *token, int fd_pipe[2], t_all *main);

/*DIR Redirection*/
int			ft_set_bool_redir(t_type *token, char *redir);
int			ft_write_fd(int fd, char *limiter, t_all *main);
int			ft_search_redir(t_type *token, char *redir);
int			ft_count_redirection(t_type *token);
char		*ft_find_name_file(char *str);
char		**ft_clear_matrix(char **matrix);
void		ft_heredoc(t_type *token, t_all *main);
void		ft_input_redirect(t_type *token);
void		ft_output_redirect(t_type *token, t_all *main);
void		ft_delete_redirection(t_type *token);
void		ft_execute_multi_redir(t_type *token);
void		ft_single_redir(t_type *token, t_all *main);
void		ft_set_new_valus(t_type *token, char *line);
void		ft_change_name_file(t_all *main, t_type *token, char redir);
void		ft_single_redir(t_type *token, t_all *main);
t_type		*ft_redirections(t_type *token, t_all *main);

/*Dir Expan Dollar*/
int			ft_check_expand(char *line, int i);
char		*ft_change_var_in_dollar(int start, int l, char *str, t_all *main);
char		*ft_expand_doll(char *line, t_all *main, int i);
char		*ft_expand_heredoc(char *line, t_all *main);
void		ft_execute_dollar(t_type *token, t_all *main);
bool		ft_expand_check(char *line);

/*temporary*/
void		ft_print_lst(t_type *a);

#endif