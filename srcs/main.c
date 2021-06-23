/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:23:25 by sschmele          #+#    #+#             */
/*   Updated: 2021/06/21 21:38:13 by sschmele         ###   ########.fr       */
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
	if ((arguments = prepare_arguments(&argc, argv)) == NULL)
		return (usage());
	redirect_signals();
	make_fullscreen();
	result = main_start_selection(argc, (const char**)arguments);
	reset_terminal_mode();
	reset_canonical_input();
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
	arguments = (char**)ft_xmalloc(sizeof(char*) * (*argc - 1));
	i_old = -1;
	j_new = 0;
	while (++i_old < (*argc - 1))
	{
		tmp_arg = ft_strtrim(argv[i_old + 1]);
		if (ft_strlen(tmp_arg) != 0)
			arguments[j_new++] = tmp_arg;
		else
		{
			free(tmp_arg);
			tmp_arg == NULL;
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

/*
** Here we save all the arguments to the structure that is
** a tree and save the pointer to the structure in static variables
** for the times user uses some signals
** Plus we locate the arguments according to the terminal size
*/

char			*main_start_selection(int argc, const char **argv)
{
	t_args		*list;
	char		*result;
	size_t		max_len;
	int			flag;

	flag = 0;
	max_len = 0;
	list = save_arguments(&max_len, argc, argv);
	save_for_exit(list, 1);
	resize_monitor(list, argc, max_len, &flag);
	result = read_commands(&list, &flag);
	if (list != NULL)
		free_arguments(list);
	return (result);
}

char			*generate_selected_line(t_args *list, char *result)
{
	char		**pointers;
	size_t		i;
	size_t		j;
	int			total;

	total = 0;
	j = -1;
	pointers = find_selected(list, &total, &j);
	if (total == 0)
	{
		free(pointers);
		return (NULL);
	}
	result = (char*)ft_xmalloc(total + 2 + (j - 1));
	i = -1;
	while (++i < j)
	{
		result = ft_strcat(result, pointers[i]);
		result = ft_straddsy(result, ' ');
	}
	result = ft_strcat(result, pointers[i]);
	free(pointers);
	return (result);
}

/*
** @*j and @total - all because of the norm, I'm sorry for that
*/

char			**find_selected(t_args *list, int *total, size_t *j)
{
	char		**pointers;
	t_args		*run;
	int			total_args_left;
	size_t		i;

	total_args_left = args_total(list, list);
	pointers = (char**)ft_xmalloc(sizeof(char*) * total_args_left + 1);
	pointers[total_args_left] = 0;
	run = list;
	i = -1;
	while (++i < total_args_left)
	{
		if (run->selected == 1)
		{
			*total += run->len;
			pointers[++(*j)] = run->arg;
		}
		run = run->next;
	}
	return (pointers);
}
