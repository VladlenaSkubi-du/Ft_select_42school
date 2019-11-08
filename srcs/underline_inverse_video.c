/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underline_inverse_video.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:00:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/08 14:16:08 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			underline_on(void)
{
	char		buf[10];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("us", &buffer), 1, ft_putint);
	buffer = buf;
}

void			underline_off(void)
{
	char		buf[10];
	char		*buffer;

	buffer = buf;
	tputs(tgetstr("ue", &buffer), 1, ft_putint);
	buffer = buf;
}

void			position_and_clear_arg(int x, int y, size_t len)
{
	char		buf[30];
	char		*buffer;
	char		*position_cursor;
	char		*clear_arg;
	
	buffer = buf;
	position_cursor = tgetstr("cm", &buffer);
	clear_arg = tgetstr("ec", &buffer);
	buffer = buf;
	tputs(tgoto(position_cursor, x, y), 1, ft_putint);
	tputs(tgoto(clear_arg, y, len), 1, ft_putint);
}