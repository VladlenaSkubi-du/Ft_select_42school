/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:50:30 by sschmele          #+#    #+#             */
/*   Updated: 2021/06/20 14:45:09 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			usage(void)
{
	ft_putendl_fd("usage: ft_select [argv1] [argv2] ...", STDOUT_FILENO);
	return (0);
}

int			terminal_errors(int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("Can not find terminal or termcap base.", STDERR_FILENO);
		ft_putstr_fd(" Please, choose one and define ", STDERR_FILENO);
		ft_putendl_fd("the \"TERM\" variable", STDERR_FILENO);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("Can't change terminal and ", STDERR_FILENO);
		ft_putendl_fd("start the program.", STDERR_FILENO);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("Input or error stream is closed. ", STDERR_FILENO);
		ft_putendl_fd("Ft_select can not work without them", STDERR_FILENO);
	}
	return (1);
}

/*
** Describes errors-messages: after such messages the program does not do
** exit but waits for the necessary action.
*/

void			message_resize(void)
{
	ft_putendl_fd("Not enough space for output.", STDERR_FILENO);
	ft_putendl_fd("Please, resize the terminal window.", STDERR_FILENO);
}
