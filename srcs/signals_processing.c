/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:29:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/14 15:09:05 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** key == 3 - SIGINT
** key == 4 - SIGTERM
** key == 28 - SIGQUIT
** key == 26 - SIGTSTP
** resize - SIGWINCH
*/

void			redirect_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGCONT, signal_handler);
}

void			signal_handler(int sig)
{
	if (sig == SIGINT)
		printf("SIGINT\n");
	if (sig == SIGTERM)
		printf("SIGTERM\n");
	if (sig == SIGQUIT)
		printf("SIGQUIT\n");
	if (sig == SIGTSTP)
		printf("SIGTSTP\n");
	if (sig == SIGWINCH)
		printf("SIGWINCH\n");
	if (sig == SIGCONT)
		printf("SIGCONT\n");
}
