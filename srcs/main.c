/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:23:25 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 18:51:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				main(int argc, char **argv)
{
	char			*termtype;
	char			room_termtype[1024];

	if (!isatty(STDIN_FILENO))
		return(1);
	if (argc < 2)
		return (usage());
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1)	
		return (terminal_errors(0));
	if (terminal_init_start(argc - 1, &argv[1]) < 0)
		return (terminal_errors(1));
	return (0);
}
