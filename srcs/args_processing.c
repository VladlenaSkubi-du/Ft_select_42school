/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:25:47 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/08 15:19:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//need functions: selected argument from the array
//replace all the arguments if screen changes

int				args_total(const t_args *list)
{
	t_args		*run;
	int			total;
	
	run = (t_args*)list;
	total = 0;
	while (run->next != list)
	{
		total++;
		run = run->next;
	}
	return (total + 1);
}

void			position_and_output_arguments(const t_args *list)
{
	t_args		*run;
	size_t		i;
	int			total;

	if (list == NULL)
		return ;
	run = (t_args*)list;
	i = 0;
	total = args_total((const t_args*)list);
	while (i < total)
	{
		if (run->underline == 1)
		{
			underline_on();
			ft_putendl_fd(run->arg, 1);
			underline_off();
		}
		else
			ft_putendl_fd(run->arg, 1);
		run = run->next;
		i++;
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