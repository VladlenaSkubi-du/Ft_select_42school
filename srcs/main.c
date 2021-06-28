/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:23:25 by sschmele          #+#    #+#             */
/*   Updated: 2021/06/23 23:19:52 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Here we check if the terminal exists, environment is ready,
** arguments are given
** and start a "new" terminal
** Tests:
** to check if terminal exists, delete TERM from the environment
** % unset TERM
** closing the STDIN_FILENO
** % ./ft_select `ls` 0<&- (the same with 1<&- and 2<&-)
** 
*/

int				main(int argc, char **argv)
{
	char			*termtype;
	char			room_termtype[1024];
	char			**arguments;
	char			*result;

	if (!isatty(STDIN_FILENO) || !isatty(STDERR_FILENO))
		return (terminal_errors(2));
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1)
		return (terminal_errors(0));
	if (set_noncanonical_input() < 0)
		return (terminal_errors(1));
			// printf("args = %d\n", argc);
	if ((arguments = prepare_arguments(&argc, argv)) == NULL)
		return (usage());
			// printf("args = %d\n", argc);
	before_start();
	result = main_start_selection(argc, (const char**)arguments);
	before_finish();
	(result != NULL) ? ft_putendl_fd(result, STDOUT_FILENO) :
		ft_putchar_fd('\n', STDOUT_FILENO);
	free(result);
	ft_arrdel(arguments);
	return (0);
}

char			**prepare_arguments(int *argc, char **argv)
{
	char		**arguments;
	char		*tmp_arg;
	int			i_old;
	int			j_new;
	
	if (*argc < 2)
		return (NULL);
	arguments = (char**)ft_xmalloc(sizeof(char*) * (*argc));
	i_old = -1;
	j_new = 0;
	while (++i_old < (*argc))
	{
		tmp_arg = ft_strtrim(argv[i_old + 1]);
		if (ft_strlen(tmp_arg) != 0)
			arguments[j_new++] = tmp_arg;
		else
		{
			free(tmp_arg);
			tmp_arg = NULL;
		}
	}
	free(tmp_arg);
	if (j_new == 0)
	{
		free(arguments);
		return (NULL);
	}
	*argc = j_new;
	return (arguments);
}

int				before_start(void)
{
	redirect_signals();
	make_fullscreen();
	hashtable_init();
	save_clean_hashdata_function(&clean_hashdata);
	return (0);
}

int				before_finish(void)
{
	reset_terminal_mode();
	reset_canonical_input();
	return (0);
}
