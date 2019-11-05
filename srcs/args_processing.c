/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:25:47 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/05 20:44:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//nothing works

void			init_argument(t_args *current, char *argument, short flag)
{
	if (flag == 0)
	{
		current->arg = ft_strdup(argument);
		current->next = current;
		current->prev = current;
	}
	else if (flag == 1)
	{
		current->next = ft_xmalloc(sizeof(t_args*));
		current->next->arg = ft_strdup(argument);
		current->next->prev = current;
		current->prev->next = current;
	}
	else
	{
		current->next = ft_xmalloc(sizeof(t_args*));
		current->next->arg = ft_strdup(argument);
		current->next->prev = current;
		current->next->next = current->prev;
		current->prev->next = current->next;
	}
	current->selected = 0;
	current->cursor = 0;
}

t_args			*save_arguments(int argc, char **argv)
{
	t_args		*list;
	t_args		*run;
	size_t		i;

	list = ft_xmalloc(sizeof(t_args*));
	run = list;
	i = 0;
	while (i < argc)
	{
		init_argument(run, argv[i], i);
		run = (i > 0) ? run->next : run;
		i++;
	}
	return (list);
}

void			output_arguments(t_args *list)
{
	t_args		*run;
	size_t		i;

	run = list;
	i = 0;
	while (i < 6)
	{
		ft_putendl(run->arg);
		run = run->next;
		i++;
	}
}

void			clean_arguments(t_args *list)
{
	
}