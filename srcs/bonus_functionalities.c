/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functionalities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:20:32 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/08 15:34:33 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			bell_sound(t_args *under)
{
	char		buf[30];
	char		*buffer;
	char		*position_cursor;

	buffer = buf;
	position_cursor = tgetstr("cm", &buffer);
	tputs(tgoto(position_cursor, under->x, under->y), 1, ft_putint);
	tputs(tgetstr("bl", &buffer), 1, ft_putint);
	buffer = buf;
}