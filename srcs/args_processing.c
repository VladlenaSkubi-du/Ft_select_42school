/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:25:47 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/12 21:13:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//need functions: selected argument from the array
//replace all the arguments if screen changes

int				args_total(const t_args *list, const t_args *under)
{
	t_args		*run;
	int			total;
	
	run = (t_args*)under;
	total = 0;
	while (run->next != list)
	{
		total++;
		run = run->next;
	}
	return (total + 1);
}

void			output_arguments(const t_args *list, const t_args *under)
{
	t_args		*run;
	int			total;
	int			i;

	if (list == NULL)
		return ;
	run = (t_args*)under;
	total = args_total((const t_args*)list, under);
	i = 0;
	underline_on();
	ft_putstr_fd(run->arg, 2);
	underline_off();
	while (++i < total)
	{
		run = run->next;
		position_cursor(run->x, run->y);
		ft_putstr_fd(run->arg, 2);
	}
}

t_args			*delete_argument(t_args *list, t_args *selected)
{
	t_args		*save;
	
	save = selected->next;
	if (list == selected)
	{
		free(selected->arg);
		free(selected);
		return (NULL);
	}
	else if (list->next == selected && list->prev == selected)
	{
		list->next = list;
		list->prev = list;
	}
	else
	{
		selected->prev->next = save;
		save->prev = selected->prev;
	}
	free(selected->arg);
	free(selected);
	save->underline = 1;
	return (save);
}

void			free_arguments(t_args *list) 
{
	t_args		*run;

	run = list;
	while (run != NULL)
		run = delete_argument(list, list->next);
}