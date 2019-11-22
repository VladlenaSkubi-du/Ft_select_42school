/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_initiation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:31:44 by sschmele          #+#    #+#             */
/*   Updated: 2019/11/20 14:01:41 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_args			*save_arguments(int argc, const char **argv)
{
	t_args		*list;
	t_args		*run;
	size_t		i;
	
	list = init_first_argument(argv[0], NULL);
	list->type = find_type(list->path_head, list->arg);
	run = list;
	i = 0;
	while (++i < argc)
	{
		if ((argv[i] = ft_strtrim(argv[i])) == NULL)
			continue ;
		init_next_argument(run, argv[i], i);
		run->next->type = find_type(list->path_head, run->next->arg);
		if (run->len > list->max_len_head)
			list->max_len_head = run->len;
		run = run->next;
	}
	list->max_len_head = (list->max_len_head == 8) ?
		(list->max_len_head)++ : list->max_len_head;
	while (list->max_len_head % 8 != 0)
		(list->max_len_head)++;
	return (list);
}

t_args			*init_first_argument(const char *argument, char *path)
{
	t_args		*list;

	list = ft_xmalloc(sizeof(t_args));
	list->arg = ft_strdup(argument);
	list->len = ft_strlen(argument);
	list->next = list;
	list->prev = list;
	list->selected = 0;
	list->underline = 1;
	list->x = 0;
	list->y = 0;
	list->max_len_head = list->len;
	if (path == NULL)
		list->path_head = ft_strdup("./");
	else
		list->path_head = ft_strdup(path);
	return (list);
}

void			init_next_argument(t_args *current,
					const char *argument, short flag)
{
	t_args		*tmp;
	t_args		*save;

	tmp = ft_xmalloc(sizeof(t_args));
	tmp->arg = ft_strdup(argument);
	tmp->len = ft_strlen(argument);
	tmp->selected = 0;
	tmp->underline = 0;
	tmp->x = 0;
	tmp->y = 0;
	if (flag == 1)
	{
		tmp->next = current;
		current->next = tmp;
		tmp->prev = current;
		current->prev = tmp;
	}
	else
	{
		save = current->next;
		tmp->next = save;
		current->next = tmp;
		tmp->prev = current;
		save->prev = tmp;
	}
}

t_args			*save_files(char *path)
{
	t_args		*list;
	t_args		*run;
	size_t		i;
	DIR			*directory;
	struct dirent		*entry;

	
	if (!(directory = opendir(path)))
		return (NULL);
	i = 0;
	while ((entry = readdir(directory)))
	{
		if (*entry->d_name == '.')
			continue;
		if (i == 0)
			list = init_first_argument(entry->d_name, path);
		else if (i > 0)
		{
			run = list;
			init_next_argument(run, entry->d_name, i);
			run->next->type = find_type(list->path_head, run->next->arg);
			if (run->len > list->max_len_head)
				list->max_len_head = run->len;
			run = run->next;
		}
		i++;
	}
	if (i == 0)
		return (NULL);
	list->max_len_head = (list->max_len_head == 8) ?
		(list->max_len_head)++ : list->max_len_head;
	while (list->max_len_head % 8 != 0)
		(list->max_len_head)++;
	closedir(directory);
	return (list);
}

char			find_type(char *path, char *argument)
{
	DIR			*dirname;
	char		*dir_name;

	dir_name = ft_strjoin(path, argument);
	if (!(dirname = opendir(dir_name)))
		return ('r');
	closedir(dirname);
	free(dir_name);
	return('d');
}
