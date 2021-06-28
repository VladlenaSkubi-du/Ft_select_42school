/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_start_finish.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 23:11:13 by a18979859         #+#    #+#             */
/*   Updated: 2021/06/23 23:14:26 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Here we save all the arguments to the structure that is
** a tree and save the pointer to the structure in static variables
** for the times user uses some signals
** Plus we locate the arguments according to the terminal size
*/

char			*main_start_selection(int argc, const char **argv)
{
	t_args		*list;
	char		*result;
	size_t		max_len;
	int			flag;

	flag = 0;
	max_len = 0;
	list = save_arguments(&max_len, argc, argv);
	save_for_exit(list, 1);
	resize_monitor(list, argc, max_len, &flag);
	result = read_commands(&list, &flag);
	if (list != NULL)
		free_arguments(list);
	return (result);
}

/*
** We finish the program by users push of the button
** This function is called in readline.c file
*/

char			*generate_selected_line(t_args *list, char *result)
{
	char		**pointers;
	size_t		i;
	size_t		j;
	int			total;

	total = 0;
	j = -1;
	pointers = find_selected(list, &total, &j);
	if (total == 0)
	{
		free(pointers);
		return (NULL);
	}
	result = (char*)ft_xmalloc(total + 2 + (j - 1));
	i = -1;
	while (++i < j)
	{
		result = ft_strcat(result, pointers[i]);
		result = ft_straddsy(result, ' ');
	}
	result = ft_strcat(result, pointers[i]);
	free(pointers);
	return (result);
}

/*
** @*j and @total - all because of the norm, I'm sorry for that
*/

char			**find_selected(t_args *list, int *total, size_t *j)
{
	char		**pointers;
	t_args		*run;
	int			total_args_left;
	size_t		i;

	total_args_left = args_total(list, list);
	pointers = (char**)ft_xmalloc(sizeof(char*) * total_args_left + 1);
	pointers[total_args_left] = 0;
	run = list;
	i = -1;
	while (++i < total_args_left)
	{
		if (run->selected == 1)
		{
			*total += run->len;
			pointers[++(*j)] = run->arg;
		}
		run = run->next;
	}
	return (pointers);
}