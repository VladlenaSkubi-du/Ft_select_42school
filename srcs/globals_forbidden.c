/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals_forbidden.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:12:03 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/20 13:34:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** @flag = 0 - we have SIGINT by ctrl-C or SIGQUIT by ctrl-\ signal
** and need to restore everithing;
** = 1 - we need to save t_args *list;
** = 2 - we have SIGTSTP signal by ctrl-Z and need to reset terminal;
** = 3 - we have SIGCONT signal by fg and need to reset program settings
*/

void						save_for_exit(t_args *list, int flag)
{
	static t_args			*list_saved;

	if (flag == 1)
		list_saved = list;
	else if (flag == 2)
	{
		reset_terminal_mode();
		reset_canonical_input();
		signal(SIGTSTP, SIG_DFL);
		ioctl(2, TIOCSTI, "\032");
	}
	else if (flag == 3)
	{
		back_to_noncanonical_input();
		redirect_signals();
		signal(SIGCONT, SIG_DFL);
		make_fullscreen();
		resize_monitor(NULL, 0);
	}
	else
	{
		reset_terminal_mode();
		reset_canonical_input();
		ft_putstr_fd(((flag == 0) ? "^C\n" : "^\\\n"), 1);
	}
}

void						resize_monitor(t_args *list, int *flag)
{
	static t_args			*list_saved;
	static int				*flag_save;

	clean_screen();
	if (list != NULL)
	{
		list_saved = list;
		flag_save = flag;
	}
	if (calculate_position(list_saved) == 1)
	{
		output_arguments((const t_args*)list_saved, (const t_args*)list_saved);
		*flag_save = 1;
	}
	else
	{
		message_resize();
		*flag_save = -1;
	}
}

/*
position_cursor(0, 0);
	ft_putstr_fd(argument, 2);
	if (!(directory = opendir(argument)))
	{
		if (errno == ENOTDIR)
			ft_putstr_fd("HERE13", 2);
		if (errno == ENOENT)
			ft_putstr_fd("HERE14", 2);
		position_cursor(50, 5);
		ft_putstr_fd("HERE1", 2);
		list->type = 'r';
	}
	else
	{
		position_cursor(50, 6);
		ft_putstr_fd("HERE", 2);
		list->type = 'd';
	}
	*/