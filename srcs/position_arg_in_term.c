/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_arg_in_term.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:33:08 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 21:02:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			fill_in_position(t_args *list, int term_lines, int max_len)
{
	t_args		*run;
	int			i;
	int			j;

	run = list;
	i = 0;
	j = 0;
	while (run->next != list)
	{
		run = run->next;
		if (max_len == 0)
			run->y = ++j;
		else
		{
			run->x = i;
			run->y = ++j;
			if (j == term_lines - 1)
			{
				i += max_len;
				j = -1;
			}
		}
	}
}

int			calculate_position(t_args *list, int total, size_t max_len)
{
	int			term_lines;
	int			term_columns;
	int			max_columns;
	int			max_capability;

	term_lines = tgetnum("li");
	term_columns = tgetnum("co");
	max_columns = term_columns / max_len;
	max_capability = max_columns * term_lines;
	if (total > max_capability)
		return (-1);
	if (total <= term_lines)
		fill_in_position(list, 0, 0);
	else
		fill_in_position(list, term_lines, max_len);
	return (1);
}