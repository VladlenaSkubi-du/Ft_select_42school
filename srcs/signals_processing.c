/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:29:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/15 18:37:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** key == 3 - SIGINT
** key == 4 - SIGTERM
** key == 28 - SIGQUIT(Ctrl-\) 
** key == 26 - SIGTSTP (ctrl-Z)
** resize - SIGWINCH
*/

void			redirect_signals(void)
{
	signal(SIGWINCH, signal_handler);
	// signal(SIGINT, signal_handler);
	// signal(SIGTERM, signal_handler);
	// signal(SIGQUIT, signal_handler);
	// signal(SIGTSTP, signal_handler);
	//signal(SIGCONT, signal_handler);
}

void			signal_handler(int sig)
{
	if (sig == SIGINT)
		;
	// if (sig == SIGTERM)
	// 	printf("SIGTERM\n");
	// if (sig == SIGQUIT)
	// 	printf("SIGQUIT\n");
	// if (sig == SIGTSTP)
	// 	printf("SIGTSTP\n");
	if (sig == SIGWINCH)
		resize_monitor(NULL, 0, 0, 0);
	// if (sig == SIGCONT)
	// 	printf("SIGCONT\n");
}

// void						save_for_exit(t_args *list, struct termios save_terminal_mode)
// {
// 	static struct termios	save_terminal_mode_exit;
// 	t_args					*list_save;

	
// }

void                resize_monitor(t_args *list, int argc,
						size_t max_len, int *flag)
{
    static t_args   *list_saved;
    static int      argc_saved;
    static size_t   max_len_saved;
	static int		*flag_save;

	clean_screen();
    if (list != NULL && argc != 0 && max_len != 0)
    {
        list_saved = list;
        argc_saved = argc;
        max_len_saved = max_len;
		flag_save = flag;
    }
	if (calculate_position(list_saved, argc_saved, max_len_saved) == 1)
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