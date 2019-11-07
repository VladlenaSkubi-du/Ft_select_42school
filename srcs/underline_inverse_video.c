/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underline_inverse_video.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:00:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/07 20:20:39 by sschmele         ###   ########.fr       */
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