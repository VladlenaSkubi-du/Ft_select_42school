/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:58:09 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 21:21:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** `sc' stays for save_cursor_position and
** `rc' stays for restor_cursor_position
*/

void			output_element(char *element)
{
	char		buf[30];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("sc", &buffer), 1, ft_putint);
	ft_putstr_fd(element, 2);
	tputs(tgetstr("rc", &buffer), 1, ft_putint);
	buffer = buf;
}

void			position_cursor(int x, int y)
{
	char		buf[20];
	char		*buffer;

	buffer = buf;
	tputs(tgoto(tgetstr("cm", &buffer), x, y), 1, ft_putint);
	buffer = buf;
}

void			position_and_clear_element(int x, int y, size_t len)
{
	char		buf[10];
	char		*buffer;
	char		*clear_arg;

	buffer = buf;
	clear_arg = tgetstr("ec", &buffer);
	buffer = buf;
	position_cursor(x, y);
	tputs(tgoto(clear_arg, y, len), 1, ft_putint);
}