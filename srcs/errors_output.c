/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:50:30 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/05 17:00:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int         usage(void)
{
	ft_putendl_fd("usage: ft_select [argv1] [argv2] ...", 1);
	return (0);
}

int         terminal_errors(int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("Can not find terminal or termcap base. ", 2);
		ft_putendl_fd("Please, choose one and define the \"TERM\" variable", 2);
	}
	else if (flag == 1)
		ft_putendl_fd("Can't change terminal and start the program.", 2);
	return (1);
}